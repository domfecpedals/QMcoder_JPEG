I = imread('clock1.jpg');
K = medfilt2(I(:,:,1),[5 5]);
% figure, imshow(K)
imwrite(K,'c1.jpg');

I = imread('clock2.jpg');
K = medfilt2(I(:,:,1),[5 5]);
% figure, imshow(K)
imwrite(K,'c2.jpg');

I = imread('clock3.jpg');
K = medfilt2(I(:,:,1),[5 5]);
% figure, imshow(K)
imwrite(K,'c3.jpg');

I = imread('clock4.jpg');
K = medfilt2(I(:,:,1),[5 5]);
% figure, imshow(K)
imwrite(K,'c4.jpg');

I = imread('clock5.jpg');
K = medfilt2(I(:,:,1),[5 5]);
% figure, imshow(K)
imwrite(K,'c5.jpg');

I = imread('pepper1.jpg');
K(:,:,1) = medfilt2(I(:,:,1),[5 5]);
K(:,:,2) = medfilt2(I(:,:,2),[5 5]);
K(:,:,3) = medfilt2(I(:,:,3),[5 5]);
% figure, imshow(K)
imwrite(K,'p1.jpg');

I = imread('pepper2.jpg');
K(:,:,1) = medfilt2(I(:,:,1),[5 5]);
K(:,:,2) = medfilt2(I(:,:,2),[5 5]);
K(:,:,3) = medfilt2(I(:,:,3),[5 5]);
% figure, imshow(K)
imwrite(K,'p2.jpg');

I = imread('pepper3.jpg');
K(:,:,1) = medfilt2(I(:,:,1),[5 5]);
K(:,:,2) = medfilt2(I(:,:,2),[5 5]);
K(:,:,3) = medfilt2(I(:,:,3),[5 5]);
% figure, imshow(K)
imwrite(K,'p3.jpg');

I = imread('pepper4.jpg');
K(:,:,1) = medfilt2(I(:,:,1),[5 5]);
K(:,:,2) = medfilt2(I(:,:,2),[5 5]);
K(:,:,3) = medfilt2(I(:,:,3),[5 5]);
% figure, ishow(K)
imwrite(K,'p4.jpg');

I = imread('pepper5.jpg');
K(:,:,1) = medfilt2(I(:,:,1),[5 5]);
K(:,:,2) = medfilt2(I(:,:,2),[5 5]);
K(:,:,3) = medfilt2(I(:,:,3),[5 5]);
% figure, imshow(K)
imwrite(K,'p5.jpg');
