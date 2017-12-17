# etool
esay tool : small, simple, high performance and cross platform library
简单的工具库(轻量，简易，高性能和跨平台)

------------------
该工具的返回值有三种
1 : 如果是create后缀或者带有创建含义的函数,则0为失败,非0为成功
2 : 如果带有强烈真假含义的函数,则0为失败,非0为成功
3 : 剩余的普通函数则0为成功,非0为失败(与系统函数返回值保持一致)