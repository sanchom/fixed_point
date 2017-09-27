import os

env = Environment(ENV = os.environ)

env.Append(CCFLAGS = ['-std=c++14', '-O3', '-Wall', '-pedantic'])
env.Append(LIBS = ['glog', 'gtest'])

env.Program('fixed_point_test.cc')
