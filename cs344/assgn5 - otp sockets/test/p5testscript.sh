#!/bin/bash
usage="usage: $0 encryptionport decryptionport"

# use custom bin directory
BIN_DIR=..

#Make sure we have the right number of arguments
if test $# -gt 2 -o $# -lt 2
then
	echo $usage 1>&2
	exit 1
fi

#Clean up any previous runs
echo '# Initializing - Cleaning up - ignore Operation Not Permitted errors'
killall -q -u $USER dec_client
killall -q -u $USER dec_server
killall -q -u $USER enc_client
killall -q -u $USER enc_server
rm -f ciphertext*
rm -f plaintext*_*
rm -f key20
rm -f key70000

#Record the ports passed in
encport=$1
decport=$2

#Run the daemons
$BIN_DIR/enc_server $encport &
$BIN_DIR/dec_server $decport &

sleep 1

echo
echo '#-----------------------------------------'
echo '# START OF GRADING SCRIPT'
echo '# keygen 20 > key20'
$BIN_DIR/keygen 20 > key20
echo "# 5 POINTS: key20 must exist"
[ -s key20 ] || rm -f key20 # remove if empty
[ -f key20 ] && echo 'key20 exists!' || echo 'key20 DOES NOT EXIST'
echo
echo "#-----------------------------------------"
echo "# 5 POINTS: Number of characters in key20, should be 21:"
wc -m key20
echo
echo "#-----------------------------------------"
echo '# keygen 70000 > key70000'
$BIN_DIR/keygen 70000 > key70000
echo "# 5 POINTS: Number of characters in key70000, should be 70001:"
[ -s key70000 ] || rm -f key70000
wc -m key70000
echo
echo "#-----------------------------------------"
echo '# enc_client plaintext1 key20 $encport'
echo "# 10 POINTS: Should return error about too-short key"
$BIN_DIR/enc_client plaintext1 key20 $encport
echo
echo "#-----------------------------------------"
echo '# enc_client plaintext1 key70000 $encport'
echo "# 20 POINTS: Should return encrypted version of plaintext1"
$BIN_DIR/enc_client plaintext1 key70000 $encport
echo
echo '#-----------------------------------------'
echo '# enc_client plaintext1 key70000 $encport > ciphertext1'
$BIN_DIR/enc_client plaintext1 key70000 $encport > ciphertext1
echo "# 10 POINTS: ciphertext1 must exist"
[ -s ciphertext1 ] || rm -f ciphertext1
[ -f ciphertext1 ] && echo 'ciphertext1 exists!' || echo 'ciphertext1 DOES NOT EXIST'
echo
echo '#-----------------------------------------'
echo '# 10 POINTS: ciphertext1 must be same number of chars as source'
echo '# wc -m plaintext1'
wc -m plaintext1
echo '# Should be same: wc -m ciphertext1'
wc -m ciphertext1
echo
echo '#-----------------------------------------'
echo '# 5 POINTS: ciphertext1 should look encrypted'
cat ciphertext1
echo
echo '#-----------------------------------------'
echo '# dec_client ciphertext1 key70000 $encport'
echo '# 5 POINTS: Should fail giving error that dec_client cannot use enc_server'
$BIN_DIR/dec_client ciphertext1 key70000 $encport
echo
echo '#-----------------------------------------'
echo '# 20 POINTS: should return decrypted ciphertext1 that matches source'
echo '# cat plaintext1'
cat plaintext1
echo '# dec_client ciphertext1 key70000 $decport'
$BIN_DIR/dec_client ciphertext1 key70000 $decport
echo
echo '#-----------------------------------------'
echo '# dec_client ciphertext1 key70000 $decport > plaintext1_a'
$BIN_DIR/dec_client ciphertext1 key70000 $decport > plaintext1_a
echo "# 10 POINTS: plaintext1_a must exist"
[ -s plaintext1_a ] || rm -f plaintext1_a
[ -f plaintext1_a ] &&  echo 'plaintext1_a exists!' || echo 'plaintext1_a DOES NOT EXIST'
echo
echo '#-----------------------------------------'
echo '# cmp plaintext1 plaintext1_a'
echo '# 5 POINTS: plaintext1 must be the same as plaintext1_a:'
echo '# echo $? should be == 0, which means the cmp succeeded!'
cmp plaintext1 plaintext1_a
echo $?
echo
echo '#-----------------------------------------'
echo '# 20 POINTS: concurrent test of encryption - look for 4 properly-sized ciphertext# files, or 5 where the 5th is 0 bytes'
echo '# 5 POINTS: Should be only one error about plaintext5 being bad'
rm -f ciphertext*
rm -f plaintext*_*
$BIN_DIR/enc_client plaintext1 key70000 $encport > ciphertext1 &
$BIN_DIR/enc_client plaintext2 key70000 $encport > ciphertext2 &
$BIN_DIR/enc_client plaintext3 key70000 $encport > ciphertext3 &
$BIN_DIR/enc_client plaintext4 key70000 $encport > ciphertext4 &
$BIN_DIR/enc_client plaintext5 key70000 $encport > ciphertext5 &
echo '  (Ten second sleep, your program must complete in this time)'
sleep 2
ls -plA ciphertext* | awk '{print $9 " " $5}' | column -t
echo
echo '#-----------------------------------------'
echo '# 15 POINTS: concurrent test of decryption - look for 4 plaintext#_a files that match the plaintext# files'
$BIN_DIR/dec_client ciphertext1 key70000 $decport > plaintext1_a &
$BIN_DIR/dec_client ciphertext2 key70000 $decport > plaintext2_a &
$BIN_DIR/dec_client ciphertext3 key70000 $decport > plaintext3_a &
$BIN_DIR/dec_client ciphertext4 key70000 $decport > plaintext4_a &
echo '  (Ten second sleep, your program must complete in this time)'
sleep 2
ls -plA plaintext* | awk '{print $9 " " $5}' | column -t

#Clean up
echo
echo '#-----------------------------------------'
echo '# Cleaning up - ignore Operation Not Permitted errors'
killall -q -u $USER dec_client
killall -q -u $USER dec_server
killall -q -u $USER enc_client
killall -q -u $USER enc_server
rm -f ciphertext*
rm -f plaintext*_*
rm -f key20
rm -f key70000
echo
echo '# SCRIPT COMPLETE'
