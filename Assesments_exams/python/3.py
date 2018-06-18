#!/usr/bin/python
l = [("Ramu","python",99),("Jahnavi","Django",100),("Kavya","Flask",67),("Bhaskar","pyramid",87)]
print sorted(l,key=lambda s:s[1],reverse=True)
print sorted(l,key=lambda s:s[2])
