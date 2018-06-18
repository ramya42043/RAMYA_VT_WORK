#!/usr/bin/python
import numpy as np

def anagram(l):
    d, out = dict(), set()
    for word in l:
        s = np.zeros(26, dtype=int)
        for c in word:
            s[ord(c)-97] += 1
        s = tuple(s)
        try:
            out.add(d[s])
            out.add(word)
        except:
            d[s] = word
    return out
    
l =['deltas','desalt','lorry','lasted','retainers','salted','aerospace','slated','staled','resmelts']
res=anagram(l)
print res

