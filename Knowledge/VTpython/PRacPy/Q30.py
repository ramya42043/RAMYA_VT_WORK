#!/usr/bin/python
iparens = iter('(){}[]<>')
parens = dict(zip(iparens, iparens))
closing = parens.values()

def balanced(astr):
    stack = []
    for c in astr:
        d = parens.get(c, None)
	if d:
            stack.append(d)
        elif c in closing:
		if not stack or c != stack.pop():
			return False
    return not stack

print balanced('{{{<>}}}}}')
