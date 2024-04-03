# Spins up a Docker container

if [ $# -lt 2 ]; then # checks if number of arguments is less than 1
    echo "Less than 2 arguments were supplied"
    echo "Usage: 'sh spinup.sh <image name> <container name> <LED_MON_SERVER_IP> <LED_MON_SERVER_PORT> <PER_CPU(true/false)>'"
else
    # mounts local current working directory to /home/webserver/source_directory in the container
    docker run -dit --network host --name $2 --restart always -v "$(pwd)":/home/webserver/source_directory:z $1
fi