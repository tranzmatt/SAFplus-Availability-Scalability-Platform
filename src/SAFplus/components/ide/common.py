import os

userWorkspace = None

def fileResolver(filename):
  """Look in standard places for a file"""
  #if filename[0] == os.sep:  # Filename is already an absolute path
  #  if os.path.exists(filename): return filename

  if os.path.exists(filename): return filename # File exists right where specified, will also handle absolute path of course

  candidate = "resources" + os.sep + filename     # look in resources
  if os.path.exists(candidate): return candidate  
  candidate = "resources" + os.sep + "images" + os.sep + filename     # look in media
  if os.path.exists(candidate): return candidate
  if userWorkspace:
    candidate = userWorkspace + os.sep + filename     # look in the user's directory
    if os.path.exists(candidate): return candidate
  raise IOError(2,'No such file')