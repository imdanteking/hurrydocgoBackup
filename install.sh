cd third_party
# download limonp
wget https://github.com/yanyiwu/limonp/archive/refs/heads/master.zip
unzip master.zip 
mv limonp-master/include/limonp cppjieba/include/cppjieba
rm -rf master.zip limonp-master
# download cpp-httplib
wget https://github.com/yhirose/cpp-httplib/archive/refs/heads/master.zip
unzip master.zip
mv cpp-httplib-master cpp-httplib
rm -rf master.zip
cd ..
cd controller
make
./hurrydocgo
