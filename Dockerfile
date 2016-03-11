FROM 540129/waermeleitungsgleichung
RUN apt-get -y update && apt-get install -y libsdl2-image-dev && apt-get install -y libsdl2-dev
CMD Waermeblanko
