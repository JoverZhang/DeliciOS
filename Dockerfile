FROM ubuntu:22.04

COPY ./docker/apt/sources.list /etc/apt/sources.list

RUN set -x && \
    apt update && \
    apt install -y make nasm gcc-11 xorriso grub-common grub-pc-bin

RUN set -x && \
    apt install -y qemu-kvm

VOLUME /code
WORKDIR /code

CMD ["bash", "./docker/entrypoint.sh"]

