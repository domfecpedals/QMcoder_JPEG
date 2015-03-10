clc;
clear;
clearvars;
clear all;
I=imread('clock.bmp');
I1=imread('c1.jpg');
I2=imread('c2.jpg');
I3=imread('c3.jpg');
I4=imread('c4.jpg');
I5=imread('c5.jpg');

p1=psnr(I,I1);
p2 = psnr(I,I2);
p3 = psnr(I,I3);
p4 = psnr(I,I4);
p5 = psnr(I,I5);
