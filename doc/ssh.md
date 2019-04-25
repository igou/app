***ssh***


***.ssh/known_hosts***


    给访问端的计算机使用，即发起ssh的用户
    ssh会把你每个访问过计算机的公钥(public key)都记录在~/.ssh/known_hosts。当下次访问相同
    计算机时，OpenSSH会核对公钥。如果公钥不同，OpenSSH会发出警告， 避免你受到DNS Hijack之
    类的攻击
***.ssh/authorized_keys***


    是被连接的计算机使用
    ssh连接计算机的公钥如果在authorized_keys的话，就不需要密码


***apt-get***

下面两条解决依赖
apt-get -f check
apt-get -f install

apt-get autoremove
apt-get update