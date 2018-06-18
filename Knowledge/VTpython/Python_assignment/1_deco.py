
#!/usr/bin/pyhton

def q_decorate(func):
   print "q_decorate"
   def func_wrapper(name):
       print name
       return "<p>{0}</p>".format(func(name))
   return func_wrapper


def p_decorate(func):
   print "p_decorate"

   def func_wrapper(name):
       print name
       return "<p>{0}</p>".format(func(name))
   return func_wrapper

@p_decorate
@q_decorate
def get_text(name):
   return "lorem ipsum, {0} dolor sit amet".format(name)

print get_text("John")

# Outputs <p>lorem ipsum, John dolor sit amet</p>

