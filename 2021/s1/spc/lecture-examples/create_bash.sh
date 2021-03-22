# Creates a new script, gives it permission to be executed and makes it output hello world

#!/bin/bash
touch new_bash.sh
chmod 755 new_bash.sh
echo "# An auto-generated bash script!" > new_bash.sh
echo "#!/bin/bash" >> new_bash.sh
echo 'echo "Hello World from a new bash script"' >> new_bash.sh
./new_bash.sh
# rm new_bash.sh