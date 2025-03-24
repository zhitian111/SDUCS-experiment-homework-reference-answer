import os
import time

import matplotlib.pyplot as plt
import tqdm
import numpy as np

from tool import env, plotting, utils, Node
import argparse


class Rrt:
    def __init__(self, start_point, end_point, step_length, sample_rate, max_iter, env_instance):
        '''
        :param start_point: start point of the robot
        :param end_point: end point of the robot
        :param step_length: step length of the robot
        :param sample_rate: sample rate for finding new node
        :param max_iter: maximum iteration
        :param env_instance:
        '''
        self.st_point = Node(start_point)
        self.ed_point = Node(end_point)
        self.step_length = step_length
        self.sample_rate = sample_rate
        self.max_iter = max_iter
        self.nodes = [self.st_point]  # nodes of the tree

        # initialize the environment
        self.env = env_instance
        self.plotting = plotting.Plotting(start_point, end_point, self.env)
        self.utils = utils.Utils(self.env)
        self.utils.fix_random_seed()
        self.x_range = self.env.x_range
        self.y_range = self.env.y_range
        self.obs_circle = self.env.obs_circle
        self.obs_rectangle = self.env.obs_rectangle
        self.obs_boundary = self.env.obs_boundary

        # record
        self.iter_num = -1
        self.time_start = -1
        self.time_end = -1
        self.dist = -1

    def planning(self):
        '''
        planning the path
        :return:
        '''
        path = None
        convergence = False
        self.time_start = time.time()
        for i in tqdm.tqdm(range(self.max_iter)):
            node_rand = self.generate_random_node()  # generate new node
            node_near = self.nearest_neighbor(node_rand)  # find the nearest node of the new node in the tree
            node_new = self.new_state(node_near,
                                      node_rand)  # generate the new node by the direction defined by the random node
            if node_new and not self.utils.is_collision(node_near, node_new):  # if the new node is not in collision
                self.nodes.append(node_new)  # add the new node to the tree
                dist, _ = self.get_distance_and_angle(node_new, self.ed_point)
                # Termination conditions
                # if the distance between the new node and the end node is less than the step length,
                # then the new node can directly connect to the end node
                if dist <= self.step_length and not self.utils.is_collision(node_new, self.ed_point):
                    self.iter_num = i + 1
                    convergence = True
                    break
        self.time_end = time.time()
        if convergence:
            # ===========smoothing===========
            if post_processing:
                node_new=self.post_processing()
            # ==============================
            path = self.extract_path(node_new)
            self.dist = self.path_distance(path)
        return path

    def generate_random_node(self):
        '''
        generate a random node (map range as the boundary)
        :return:
        '''
        delta = self.utils.delta

        # uniform sample new node
        if np.random.random() > self.sample_rate:
            return Node((np.random.uniform(self.x_range[0] + delta, self.x_range[1] - delta),
                         np.random.uniform(self.y_range[0] + delta, self.y_range[1] - delta)))
        # sample end point as new node
        return self.ed_point

    def nearest_neighbor(self, n):
        '''
        find the nearest node in the tree
        :param n:
        :return:
        '''
        return self.nodes[int(np.argmin([np.linalg.norm([nd.x - n.x, nd.y - n.y])
                                         for nd in self.nodes]))]

    def new_state(self, node_start, node_end):
        '''
        generate the new node by the direction defined by the random node
        :param node_start:
        :param node_end:
        :return:
        '''
        dist, theta = self.get_distance_and_angle(node_start, node_end)

        dist = np.min([self.step_length, dist])
        node_new = Node((node_start.x + dist * np.cos(theta),
                         node_start.y + dist * np.sin(theta)))
        node_new.parent = node_start

        return node_new

    def extract_path(self, node_end):
        '''
        extract the path from the end node by backtracking
        :param node_end:
        :return:
        '''
        path = [(self.ed_point.x, self.ed_point.y)]
        node_now = node_end

        while node_now.parent is not None:
            node_now = node_now.parent
            path.append((node_now.x, node_now.y))

        return path

    def path_distance(self, path):
        '''
        get the distance of the path
        :param path:
        :return:
        '''
        dist_sum = 0
        for i in range(len(path) - 1):
            dist_sum += np.linalg.norm([path[i + 1][0] - path[i][0], path[i + 1][1] - path[i][1]])
        return dist_sum

    def get_distance_and_angle(self, node_start, node_end):
        '''
        get the distance and angle between two nodes
        :param node_start:
        :param node_end:
        :return:
        '''
        dx = node_end.x - node_start.x
        dy = node_end.y - node_start.y
        return np.linalg.norm([dx, dy]), np.arctan2(dy, dx)

    def post_processing(self):
        print("POST_PROCESSING ON")
        self.ed_point.parent=self.nodes[-1]
        smooth_start=self.st_point
        smooth_end=self.ed_point
        while smooth_start!=self.ed_point:
            while smooth_end.parent!=smooth_start:
                if not self.utils.is_collision(smooth_start, smooth_end):
                    smooth_end.parent=smooth_start
                    break
                smooth_end=smooth_end.parent
            smooth_start=smooth_end
            smooth_end=self.ed_point
        return self.ed_point.parent


def env1_planning(eval_time=1):
    x_start = (5, 5)  # st node
    x_goal = (49, 16)  # end node

    # visualization
    if eval_time == 1:
        rrt = Rrt(x_start, x_goal, step_len, sample_rate, 10000, env.EnvOne())
        path = rrt.planning()
        if not path:
            print("No Path Found!")
        print("Time: {:.3f} s".format(rrt.time_end - rrt.time_start))
        print("Iteration:", rrt.iter_num)
        if path:
            print("Distance:{:.3f}".format(rrt.dist))
        rrt.plotting.animation(rrt.nodes, path, "RRT_ENV1", True)
        return rrt.iter_num
    # evaluation
    time_sum = list()
    iter_sum = list()
    dist_sum = list()
    for i in range(eval_time):
        rrt = Rrt(x_start, x_goal, step_len, sample_rate, 10000, env.EnvOne()) # sample rate 0.05
        path = rrt.planning()
        if not path:
            print("No Path Found!")
        print("###### Evaluation: {} ######".format(i + 1))
        print("Time: {:.3f} s".format(rrt.time_end - rrt.time_start))
        print("Iteration:", rrt.iter_num)
        if path:
            print("Distance:{:.3f}".format(rrt.dist))
            dist_sum.append(rrt.dist)
        print("-----------------------------------------------------")
        time_sum.append(rrt.time_end - rrt.time_start)
        iter_sum.append(rrt.iter_num)

    # average time
    print("Average Time: {:.3f} s".format(np.mean(time_sum)))
    # average iteration
    print("Average Iteration: {:.0f}".format(np.mean(iter_sum)))
    # average distance
    if len(dist_sum) > 0:
        print("Average Distance: {:.3f}".format(np.mean(dist_sum)))
    
    return np.mean(iter_sum)


def env2_planning(eval_time=1):
    x_start = (5, 20)  # st node
    x_goal = (67, 40)  # end node

    # visualization
    if eval_time == 1:
        rrt = Rrt(x_start, x_goal, step_len, sample_rate, 10000, env.EnvTwo())
        path = rrt.planning()
        if not path:
            print("No Path Found!")
        print("Time: {:.3f} s".format(rrt.time_end - rrt.time_start))
        print("Iteration:", rrt.iter_num)
        if path:
            print("Distance:{:.3f}".format(rrt.dist))
        rrt.plotting.animation(rrt.nodes, path, "RRT_ENV2", True)
        return
    # evaluation
    time_sum = list()
    iter_sum = list()
    dist_sum = list()
    for i in range(eval_time):
        rrt = Rrt(x_start, x_goal, step_len, sample_rate, 10000, env.EnvTwo()) # sample rate 0.2
        path = rrt.planning()
        if not path:
            print("No Path Found!")
        print("###### Evaluation: {} ######".format(i + 1))
        print("Time: {:.3f} s".format(rrt.time_end - rrt.time_start))
        print("Iteration:", rrt.iter_num)
        if path:
            print("Distance:{:.3f}".format(rrt.dist))
            dist_sum.append(rrt.dist)
        print("-----------------------------------------------------")
        time_sum.append(rrt.time_end - rrt.time_start)
        iter_sum.append(rrt.iter_num)


    # average time
    print("Average Time: {:.3f} s".format(np.mean(time_sum)))
    # average iteration
    print("Average Iteration: {:.0f}".format(np.mean(iter_sum)))
    # average distance
    if len(dist_sum) > 0:
        print("Average Distance: {:.3f}".format(np.mean(dist_sum)))


def env3_planning(eval_time=1):
    x_start = (5, 2)  # st node
    x_goal = (18, 18)  # end node

    # visualization
    if eval_time == 1:
        rrt = Rrt(x_start, x_goal, step_len, sample_rate, 10000, env.EnvThree()) # sample rate 0.05
        path = rrt.planning()
        if not path:
            print("No Path Found!")
        print("Time: {:.3f} s".format(rrt.time_end - rrt.time_start))
        print("Iteration:", rrt.iter_num)
        print("Distance:{:.3f}".format(rrt.dist))
        rrt.plotting.animation(rrt.nodes, path, "RRT_ENV3", True)
        return
    # evaluation
    time_sum = list()
    iter_sum = list()
    dist_sum = list()
    for i in range(eval_time):
        rrt = Rrt(x_start, x_goal, step_len, sample_rate, 10000, env.EnvThree())
        path = rrt.planning()
        if not path:
            print("No Path Found!")
        print("###### Evaluation: {} ######".format(i + 1))
        print("Time: {:.3f} s".format(rrt.time_end - rrt.time_start))
        print("Iteration:", rrt.iter_num)
        if path:
            print("Distance:{:.3f}".format(rrt.dist))
            dist_sum.append(rrt.dist)
        print("-----------------------------------------------------")
        time_sum.append(rrt.time_end - rrt.time_start)
        iter_sum.append(rrt.iter_num)

    # average time
    print("Average Time: {:.3f} s".format(np.mean(time_sum)))
    # average iteration
    print("Average Iteration: {:.0f}".format(np.mean(iter_sum)))
    # average distance
    if len(dist_sum) > 0:
        print("Average Distance: {:.3f}".format(np.mean(dist_sum)))

# 寻找最少迭代次数
def save_iter_counts(iter_time,eval_time=1):
    # if eval_time==1:
    #     return
    # file_name="step_len_iter_time.pkl"
    # if not os.path.exists("step_len_iter_time.pkl"):
    #     pickle.dump({},open(file_name,"wb"))
    # step_len_iter_time=pickle.load(open(file_name,"rb"))
    # step_len_iter_time[step_len]=int(iter_time)
    # pickle.dump(step_len_iter_time,open(file_name,"wb"))
    return
    

if __name__ == '__main__':
    parser=argparse.ArgumentParser()
    parser.add_argument("-s","--step_len",help="step length",type=float,default=0.5)
    parser.add_argument("-r","--sample_rate",help="sample rate",type=float,default=0.05)
    args=parser.parse_args()
    step_len=args.step_len
    sample_rate=args.sample_rate

    post_processing=False

    eval_time=1
    save_iter_counts(env1_planning(eval_time),eval_time) 
    # save_iter_counts(env2_planning(eval_time),eval_time)
    # save_iter_counts(env3_planning(eval_time),eval_time) 

