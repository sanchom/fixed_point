import os

env = Environment(ENV = os.environ)

env.Append(CPPPATH = ['/opt/local/include'])
env.Append(LIBPATH = ['/opt/local/lib'])
env.Append(CCFLAGS = ['-std=c++0x', '-O3', '-Wall'])
env.Append(LIBS = ['glog', 'gtest'])

env.Program('fixed_point_test.cc')
