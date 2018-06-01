from collections import defaultdict

zhuyin_big5 = defaultdict(lambda : set(), {})
input = open("Big5-ZhuYin.map", 'r', encoding="big5-hkscs")

for line in input:
    line = line.replace(" ", "")
    character = line[0]
    zhuyins = line[1:].split('/')
    zhuyin_big5[character].add(character)
    for zhuyin in zhuyins:
        zhuyin_big5[zhuyin[0]].add(character)
        
output = open("ZhuYin-Big5.map", 'w', encoding="big5-hkscs")
for zhuyin in zhuyin_big5:
    print(zhuyin, end="", file=output)
    for character in zhuyin_big5[zhuyin]:
        print(" ", character, end="", file=output)
    print("", file=output)
