import subprocess


hashmap = {}

wordlist = open("200000_phrases.txt", 'r')
lines = wordlist.readlines()

for i in range(len(lines)):

    if "#" in lines[i]:
        continue

    file = open("tempFile.txt", 'w')
    file.write(lines[i])
    file.close()

    proc = subprocess.Popen("../build/HashAlgorithm -f tempFile.txt",shell=True, stdout=subprocess.PIPE)

    output = proc.stdout.read()
    # print(output)

    if hashmap.get(output) is not None:
        print("repeated now:" + lines[i] + "Before "+ hashmap.get(output))

    else:
        hashmap[output] = lines[i]
