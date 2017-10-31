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
	text ='''����,��  ,����,23��/31��
	����,����,����,25��/31��
	����,����,С��,25��/30��
	��һ,С��,����,26��/32��
	�ܶ�,����,����,27��/34��
	����,����,����,28��/36��
	����,����,����,28��/36��'''
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
