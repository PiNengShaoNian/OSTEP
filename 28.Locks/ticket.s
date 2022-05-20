.var ticket  # ticket = 0
.var turn    # turn = 0
.var count

.main
.top	

.acquire
mov $1, %ax
fetchadd %ax, ticket  # ticket+1后，旧的ticket值被保存在%ax中 
.tryagain
mov turn, %cx         # %cx = turn
test %cx, %ax         # 检查turn和ticket的值是否相等
jne .tryagain         # 如果不相等，则继续自旋

# critical section
mov  count, %ax       # get the value at the address
add  $1, %ax          # increment it
mov  %ax, count       # store it back

# release lock
mov $1, %ax
fetchadd %ax, turn   # turn+1后，拥有下一张票的线程将获得锁

# see if we're still looping
sub  $1, %bx
test $0, %bx
jgt .top	

halt