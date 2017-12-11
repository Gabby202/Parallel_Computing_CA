README
##########################################################
QUICKSTART
##########################################################
To visualize you just have to run one of the two .jar .
NOT both of same at the same time, they are outputing the same file

##########################################################
REQUIEREMENT
##########################################################
This folder must contain :
	config.ini
	cygwin1.dll
	[parallel_program.exe , Simulation_parallel.jar] - optional
	[serial_program.exe , Simulation_serial.jar] - optional
	[README.md] - optional

##########################################################
UNLEASH THE POWER
##########################################################
In order to make the execution safer, all the values get from config.ini are tested
however you can launch the parallel_program and the serial_program by command line with argument to bypass this chekining for some variable.
Commande line :
program_name [CELLS [STEPS [EXPORT [THREADS]]] 

Bear in mind that with custom argument the program may not work properly (take long time, exessive RAM/CPU usage, full your memory drive, delete the internet or create killing robot)
