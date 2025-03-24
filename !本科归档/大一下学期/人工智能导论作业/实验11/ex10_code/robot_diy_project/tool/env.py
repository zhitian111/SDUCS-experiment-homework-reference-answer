class EnvOne:
    def __init__(self):
        self.x_range = (0, 50)
        self.y_range = (0, 30)
        self.obs_boundary = self.obs_boundary()
        self.obs_circle = self.obs_circle()
        self.obs_rectangle = self.obs_rectangle()

    def obs_boundary(self):
        '''
        define the boundary of the environment
        :return:
        '''
        obs_boundary = [
            [0, 0, 1, 30],
            [0, 30, 50, 1],
            [1, 0, 50, 1],
            [50, 1, 1, 30]
        ]
        return obs_boundary

    def obs_rectangle(self):
        '''
        the rectangles in the environment
        :return:
        '''
        obs_rectangle = [
            [14, 12, 8, 2],
            [18, 22, 8, 3],
            [26, 7, 2, 12],
            [32, 14, 10, 2]
        ]
        return obs_rectangle

    def obs_circle(self):
        '''
        the circles in the environment
        :return:
        '''
        obs_cir = [
            [7, 12, 3],
            [46, 20, 2],
            [15, 5, 2],
            [37, 7, 3],
            [37, 23, 3]
        ]

        return obs_cir


class EnvTwo:
    def __init__(self):
        self.x_range = (0, 70)
        self.y_range = (0, 50)
        self.obs_boundary = self.obs_boundary()
        self.obs_circle = self.obs_circle()
        self.obs_rectangle = self.obs_rectangle()

    def obs_boundary(self):
        '''
        define the boundary of the environment
        :return:
        '''
        obs_boundary = [
            [0, 0, 1, 50],
            [0, 50, 70, 1],
            [1, 0, 70, 1],
            [70, 1, 1, 50]
        ]
        return obs_boundary

    def obs_rectangle(self):
        '''
        the rectangles in the environment
        :return:
        '''
        obs_rectangle = [
            [14, 12, 8, 2],
            [18, 22, 8, 3],
            [26, 7, 2, 12],
            [32, 14, 10, 2],
            [42, 24, 20, 2],
            [20, 40, 20, 2],
            [30, 26, 5, 12],
            [50, 10, 5, 10],
            [50, 27, 5, 9],
            [50, 45, 5, 5],
            [47, 3, 10, 5],
        ]
        return obs_rectangle

    def obs_circle(self):
        '''
        the circles in the environment
        :return:
        '''
        obs_cir = [
            [7, 12, 3],
            [46, 20, 2],
            [15, 5, 2],
            [37, 7, 3],
            [37, 23, 3],
            [60, 40, 5],
            [10, 30, 7],
            [63, 10, 4],
            [50, 40, 3],
            [67, 30, 2.5],
        ]

        return obs_cir


class EnvThree:
    def __init__(self):
        self.x_range = (0, 20)
        self.y_range = (0, 20)
        self.obs_boundary = self.obs_boundary()
        self.obs_circle = self.obs_circle()
        self.obs_rectangle = self.obs_rectangle()

    def obs_boundary(self):
        '''
        define the boundary of the environment
        :return:
        '''
        obs_boundary = [
            [0, 0, 1, 20],
            [0, 20, 20, 1],
            [1, 0, 20, 1],
            [20, 1, 1, 20]
        ]
        return obs_boundary

    def obs_rectangle(self):
        '''
        the rectangles in the environment
        :return:
        '''
        obs_rectangle = [
            [8, 5, 12, 1],
            [1, 10, 15, 1],
            [5, 15, 15, 1],
        ]
        return obs_rectangle

    def obs_circle(self):
        '''
        the circles in the environment
        :return:
        '''
        obs_cir = [

        ]

        return obs_cir

class EnvFour:
    def __init__(self):
        self.x_range = (0, 20)
        self.y_range = (0, 20)
        self.obs_boundary = self.obs_boundary()
        self.obs_circle = self.obs_circle()
        self.obs_rectangle = self.obs_rectangle()

    def obs_boundary(self):
        '''
        define the boundary of the environment
        :return:
        '''
        obs_boundary = [
            [0, 0, 1, 20],
            [0, 20, 20, 1],
            [1, 0, 20, 1],
            [20, 1, 1, 20]
        ]
        return obs_boundary

    def obs_rectangle(self):
        '''
        the rectangles in the environment
        :return:
        '''
        obs_rectangle = [
            # [7,3,7,5]
        ]
        return obs_rectangle

    def obs_circle(self):
        '''
        the circles in the environment
        :return:
        '''
        obs_cir = [

        ]

        return obs_cir