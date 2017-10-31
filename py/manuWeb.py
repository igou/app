#coding: utf-8
import os
import sys
import webbrowser

class manuscriptHTML():
	'''
	1,comment need to indent
	2,class A()
	  A'method reference class var WITH A.Var
	  and member var using self.var
	3,See doc about function name that begin with '__'or '_'.eg.__fun__ _fun__  
	'''
	text ='''今天,晴  ,多云,23℃/31℃
	明天,多云,中雨,25℃/31℃
	后天,中雨,小雨,25℃/30℃
	周一,小雨,多云,26℃/32℃
	周二,多云,多云,27℃/34℃
	周三,多云,多云,28℃/36℃
	周四,多云,多云,28℃/36℃'''
	def __init__(self):
		self.simp_demo='web.html'
		self.tables = []
	def _handle_tag__(self,text):
		need_append = 1
		
		for line in text.splitlines():
			words = line.split(',')
			for i in range(len(words)):
				if need_append:
					self.tables.append([])
				self.tables[i].append(words[i])
			need_append = 0
	def _write_html(self,f):
		self._handle_tag__(manuscriptHTML.text)
		f.write('<head> test table </head> <table>')
		for _tr_ in self.tables:
			# 'sep'.join(seq)  With sep as a delimiter, all elements of seq are merged into a new string
			f.write('<tr>\n<td>'+'</td>\n<td>'.join(_tr_)+'</td>\n</tr>') #tr is row,th and td is colume of one row
		f.write('<table>')
	def show_html(self):
		f = open(self.simp_demo,'w+')
		self._write_html(f)
		f.close()
		webbrowser.open_new_tab(self.simp_demo)

if __name__ == "__main__":
	html_obj= manuscriptHTML()
	html_obj.show_html()
