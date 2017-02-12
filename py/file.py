#-*- coding: utf-8 -*-

import os
import urllib2
#class中每个函数的参数必须有self，调用时可以不管这个参数
#__init__函数中参数可以指定默认值，在实例化时可以指定参数值，可以部分指定相应的参数，
#path模块中的函数注意有些是需要传入路劲的，因为不传入path，python也不知道是哪个对象
class file_op:
	def __init__(self,argv1=3):
		#print self
		self.good = argv1
		print "class init %d"%self.good
	def get_file_size(self,dir):
		bytes = 0
		if not os.path.exist(dir):
			return 0
		if os.path.isfile(dir):
			return os.path.getsize(dir)
		for entry in os.listdir(dir):
			#print "entry %s"%entry
			newpath = os.path.join(dir,entry)
			#print newpath
			if os.path.isfile(newpath):
				#print entry
				bytes = bytes + os.path.getsize(newpath)
			else:
				#print "dir %s"%entry
				bytes = bytes + self.get_file_size(newpath) 
		return bytes
		
class catch_web(object):
	def __init__(self):
		print  "this is catching web"
		print type(self)
	def simple_demo(self,url):
		urlobj = urllib2.urlopen(url)#有3个参数，第一个是必选的
		#print urlobj.read()
	def simple_demo_req(self,url):
		req = urllib2.Request(url)  #构造request在传入open中
		rep = urllib2.urlopen(req)
		text = rep.read()
		print text

		if text.find("www")>=0:
			print "find"
		else:
			print "miss"
if __name__ == '__main__':
	total = 0
	DIR = "D:\\F\\config.ini"

	
	fileO = file_op(2334)
	total = fileO.get_file_size(DIR)
	print total
	nGB = float(total)/1024/1024/1024
	print "%0.2f GB"%nGB
	
	url = "http://www.baidu.com"
	webobj = catch_web()
	webobj.simple_demo(url)
	webobj.simple_demo_req(url)