# led_mon

## Dependencies
One of the goals of the project is to reduce external dependencies and have docker manage the dependencies
```
docker
docker-buildx
```

## Build Steps:
The `scripts/build_pipeline.sh` script will build the led_mon images and spinup a new container and automatically run the led_mon binary.
```
clone the repo
cd led_mon

# This will only build base image if not exists, may have to run a second time to build final docker image
sudo sh scripts/build_pipeline.sh 

# To view the output of led_mon bin
sudo docker logs --tail 50 --follow --timestamps led_mon

# Attatch to container if you want to
sudo sh scripts/attach.sh led_mon
```

## TODO
- [x] Create Config wrapper class to get environment variables - mainly for defining future http server ip and port
- [ ] Update build scripts to accept ip and port env vars
- [x] Create curl class to post json to http server
- [ ] Create arm variant of docker image
- [ ] Maybe create a better python wrapper class for C/C++ functions
- [ ] Add overload constructor vector PostJson for multi-cpu monitoring
