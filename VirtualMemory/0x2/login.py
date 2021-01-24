import time
import os 

def succes():
	print('='*80)
	print('\n||\t     ACCESS GRANTED     \t||\n')
	print('='*80)


print('~ Welcome ~\nPlease Login Below:')
password = 'Sup3r5ecr3tP4s5w0rd'
TARGET = raw_input('Enter Password: ')
authenticated = False
print('Your Input: %s' % TARGET)
while not authenticated:
	 print('[Password: %s, Input: %s]' % (password, TARGET))
	 if (password == TARGET):
	 	authenticated = True
	 time.sleep(3)
# if outside of while loop then *must* be logged in xD
success()


