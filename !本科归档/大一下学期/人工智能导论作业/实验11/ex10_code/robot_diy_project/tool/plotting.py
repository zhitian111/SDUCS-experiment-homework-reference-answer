import matplotlib.pyplot as plt
import matplotlib.patches as patches
import time


class Plotting:
    def __init__(self, x_start, x_goal, env_instance):
        self.xI, self.xG = x_start, x_goal
        self.env = env_instance
        self.obs_bound = self.env.obs_boundary
        self.obs_circle = self.env.obs_circle
        self.obs_rectangle = self.env.obs_rectangle

    def animation(self, nodelist, path, name, animation=False):
        self.plot_grid(name)
        self.plot_visited(nodelist, animation)
        self.plot_path(path)

    def animation_connect(self, V1, V2, path, name):
        self.plot_grid(name)
        self.plot_visited_connect(V1, V2)
        self.plot_path(path)

    def plot_grid(self, name):
        '''
        Plot the environment
        :param name:
        :return:
        '''
        #time.sleep(0.1)
        fig, ax = plt.subplots()
        for (ox, oy, w, h) in self.obs_bound:
            ax.add_patch(
                patches.Rectangle(
                    (ox, oy), w, h,
                    edgecolor='black',
                    facecolor='black',
                    fill=True
                )
            )

        for (ox, oy, w, h) in self.obs_rectangle:
            ax.add_patch(
                patches.Rectangle(
                    (ox, oy), w, h,
                    edgecolor='black',
                    facecolor='gray',
                    fill=True
                )
            )

        for (ox, oy, r) in self.obs_circle:
            ax.add_patch(
                patches.Circle(
                    (ox, oy), r,
                    edgecolor='black',
                    facecolor='gray',
                    fill=True
                )
            )

        #time.sleep(0.1)
        plt.plot(self.xI[0], self.xI[1], "bs", linewidth=3)
        #time.sleep(0.1)
        plt.plot(self.xG[0], self.xG[1], "gs", linewidth=3)

        plt.title(name)
        plt.axis("equal")

    @staticmethod
    def plot_visited(nodelist, animation):
        '''
        Plot the visited nodes
        :param nodelist:
        :param animation:
        :return:
        '''
        if animation:
            count = 0
            for node in nodelist:
                count += 1
                if node.parent:
                    #time.sleep(0.1)
                    plt.plot([node.parent.x, node.x], [node.parent.y, node.y], "-g")
                    #time.sleep(0.1)
                    plt.gcf().canvas.mpl_connect('key_release_event',
                                                 lambda event:
                                                 [exit(0) if event.key == 'escape' else None])
                    if count % 10 == 0:
                        plt.pause(0.001)
        else:
            for node in nodelist:
                if node.parent:
                    #time.sleep(0.1)
                    plt.plot([node.parent.x, node.x], [node.parent.y, node.y], "-g")

    @staticmethod
    def plot_visited_connect(V1, V2):
        '''
        plot two visited nodes simultaneously for rrt_connect.py
        :param V1:
        :param V2:
        :return:
        '''
        len1, len2 = len(V1), len(V2)

        for k in range(max(len1, len2)):
            if k < len1:
                if V1[k].parent:
                    #time.sleep(0.1)
                    plt.plot([V1[k].x, V1[k].parent.x], [V1[k].y, V1[k].parent.y], "-g")
            if k < len2:
                if V2[k].parent:
                    #time.sleep(0.1)
                    plt.plot([V2[k].x, V2[k].parent.x], [V2[k].y, V2[k].parent.y], "-g")

            #time.sleep(0.1)
            plt.gcf().canvas.mpl_connect('key_release_event',
                                         lambda event: [exit(0) if event.key == 'escape' else None])

            if k % 2 == 0:
                plt.pause(0.001)

        plt.pause(0.01)

    @staticmethod
    def plot_path(path):
        '''
        Plot the final path
        :param path:
        :return:
        '''
        if path is not None and len(path) != 0:
            #time.sleep(0.1)
            plt.plot([x[0] for x in path], [x[1] for x in path], '-r', linewidth=2)
            plt.pause(0.01)
        # plt.close()
        # plt.pause(0.001)
        # #time.sleep(0.1)
        # print("1\n")
        plt.show()
        # plt.close()
