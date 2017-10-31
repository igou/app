# coding: utf-8
import webbrowser
url = 'https://www.baidu.com/?tn=97011255_hao_pg'

from pyh import *  #download from third-part £¬ output HTML file

#following code generate html using phy module
page = PyH('phy module') 
page.addCSS('myStylesheet1.css', 'myStylesheet2.css')
page.addJS('myJavascript1.js', 'myJavascript2.js')
list=[[1,'Lucy',25],[2,'Tom',30],[3,'Lily',20]]
page << h1('My big title', cl='center')  #  (<<,operator overload)
page << div(cl='myCSSclass1 myCSSclass2', id='myDiv1') << p('I love PyH!', id='myP1')
mydiv2 = page << div(id='myDiv2')
mydiv2 << h2('A smaller title') + p('Followed by a paragraph.')
page << div(id='myDiv3')
page.myDiv3.attributes['cl'] = 'myCSSclass3'
page.myDiv3 << p('Another paragraph')
page<<div(style="text-align:center")<<h4('Test table')
mytab = page << table(border="1",cellpadding="3",cellspacing="0",style="margin:auto")
tr1 = mytab << tr(bgcolor="lightgrey")
tr1 << th('id') + th('name')+th('age')
for i in range(len(list)):
	tr2 = mytab << tr()
	for j in range(len(list)):
		tr2 << td('Row %d, column %d' % (i, j))

page.printOut('phy.html')
webbrowser.open_new_tab('phy.html')