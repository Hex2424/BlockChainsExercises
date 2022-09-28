import subprocess


hashmap = {}

wordlist = open("LT-Top500k.txt", 'r')
lines = wordlist.readlines()

for i in range(len(lines)):

    if "#" in lines[i]:
        continue

    

    proc = subprocess.Popen("../build/HashAlgorithm " + lines[i],shell=True, stdout=subprocess.PIPE)
    output = proc.stdout.read()
    # print(output)

    if hashmap.get(output) is not None:
        print("repeated now:" + lines[i] + "Before "+ hashmap.get(output))

    else:
        hashmap[output] = lines[i]
