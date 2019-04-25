"""import"""
    

    from string import ascii_lowercase
    import string
    import string.ascii_lowercase

    运行后发现最后一行代码报错：ImportError: No module named ascii_lowercase，
    意思是：“找不到叫 ascii_lowercase 的模块”。第 1 行和第 3 行的区别只在于有没有from，
    翻翻语法定义发现有这样的规则：
    import ... 后面只能是模块或包
    from ... import ... 中，from 后面只能是模块或包，import 后面可以是任何变量