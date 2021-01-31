import sys 
import os 

def swap(filename, destroy):
	data = []
	for line in open(filename, 'r').readlines():
		data.append(line.replace('\n',''))
	if destroy:
		os.remove(filename)
	return data

def examine_process_1(PID):
	stack_data = ''
	heap_data = ''


	mem_file = '/proc/%d/mem' % PID
	map_file = '/proc/%d/maps' % PID
	print('[*] Opening %s and %s' % (mem_file, map_file))

	# Find Location of head from proc
	heap_range = []
	os.system("echo $(cat %s | grep heap | cut -d '-' -f 1) >> cmd.txt" % map_file)
	heap_range.append(swap('cmd.txt',True).pop().split(' ')[0])
	os.system("echo $(cat %s | grep heap | cut -d '-' -f 2 | cut -d ' ' -f 1) >> cmd.txt" % map_file)
	heap_range.append(swap('cmd.txt',True).pop().split(' ')[0])
	print('[*] Heap is at: 0x%s-0x%s' % (heap_range[0], heap_range[1]))
	# calculate offsets 
	
	heap_start = int(heap_range[0], 16)
	heap_end = int(heap_range[1], 16)
	# Open Mem file and read the heap data
	memf = open(mem_file, 'rb+')
	memf.seek(heap_start)
	heap_data = memf.read(heap_end - heap_start)
	memf.close()

	# find location of stack from proc 
	stack_range = []
	os.system("echo $(cat %s | grep stack | cut -d '-' -f 1) >> cmd.txt" % map_file)
	stack_range.append(swap('cmd.txt',True).pop())
	os.system("echo $(cat %s | grep stack | cut -d '-' -f 2 | cut -d ' ' -f 1) >> cmd.txt" % map_file)
	stack_range.append(swap('cmd.txt',True).pop())
	print('[*] Stack is at: 0x%s-0x%s' % (stack_range[0], stack_range[1]))
	
	# calculate offsets 
	stack_start = int(stack_range[0], 16)
	stack_end = int(stack_range[1], 16)

	# Open memfile and read the stack data
	memf = open(mem_file, 'rb+')
	memf.seek(stack_start)
	stack_data = memf.read(stack_start - stack_end)
	memf.close()

	return {'heap':heap_data,'stack':stack_data}


def examine_proccess_2(NAME):
	cmd = 'ls /proc/$(pidof %s)/ | while read n; do ls -la /proc/$(pidof %s)/$n; done' % (NAME, NAME)
	os.system(cmd+' >> cmd.txt')
	# Parsing this should tell a lot about the process named

def main():
	if len(sys.argv) > 1:
		try:
			pid = int(sys.argv[1])
		except ValueError:
			pass
			try:
				os.system('pidof %s >> cmd.txt' % sys.argv[1])
				pid = int(swap('cmd.txt',True).pop().replace('\n',''))
			except:
				print('[!!] Unable to understand input')
				pass
		print('[*] Examining Process %d' % pid)
		dump = examine_process_1(pid)
		open('stack%d.txt'% pid,'wb').write(dump['stack'])
		open('heap%d.txt' % pid, 'wb').write(dump['heap'])



if __name__ == '__main__':
	main()
