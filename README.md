# logsys
A log system
<<<<<<< HEAD
The template class'instance as a member variables of another class
inherited template class logT(base class)
**The problem about the log:**
##log system
Log file is a text document that recording the log you want print everytime or everywhere; so you can know the program how to work or while the program core down or other problem, you find the position easy!
The log system is a oriented class system ,As a base template class ,as the class's father-class you want set log! But the log file is not oriented class ,it means the log file is several class's home,maybe a namespace or a module!
##log file
The log file is update or recreate when the file's size is bigger than the DEFAULT_LFSIZE(=default log file size ,you set in etc/logsys.conf). The filename is module+time-tip+suffix(.log) ,the time-tip is create time.
