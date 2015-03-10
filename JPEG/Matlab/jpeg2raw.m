x=imread('data/clock1.jpg'); 
cmodel=x(:,:,1);
fid2=fopen('data/raw/clock1.raw','w+');
cnt=fwrite(fid2,cmodel,'uint8');
fclose(fid2);

x=imread('data/clock2.jpg'); 
cmodel=x(:,:,1);
fid2=fopen('data/raw/clock2.raw','w+');
cnt=fwrite(fid2,cmodel,'uint8');
fclose(fid2);

x=imread('data/clock3.jpg'); 
cmodel=x(:,:,1);
fid2=fopen('data/raw/clock3.raw','w+');
cnt=fwrite(fid2,cmodel,'uint8');
fclose(fid2);

x=imread('data/clock4.jpg'); 
cmodel=x(:,:,1);
fid2=fopen('data/raw/clock4.raw','w+');
cnt=fwrite(fid2,cmodel,'uint8');
fclose(fid2);

x=imread('data/clock5.jpg'); 
cmodel=x(:,:,1);
fid2=fopen('data/raw/clock5.raw','w+');
cnt=fwrite(fid2,cmodel,'uint8');
fclose(fid2);


color=imread('data/pepper1.jpg'); 
cmodel=color(:,:,:);
fid2=fopen('data/raw/pepper1.raw','w+');
cnt=fwrite(fid2,cmodel,'uint8');
fclose(fid2);

color=imread('data/pepper2.jpg'); 
cmodel=color(:,:,:);
fid2=fopen('data/raw/pepper2.raw','w+');
cnt=fwrite(fid2,cmodel,'uint8');
fclose(fid2);

color=imread('data/pepper3.jpg'); 
cmodel=color(:,:,:);
fid2=fopen('data/raw/pepper3.raw','w+');
cnt=fwrite(fid2,cmodel,'uint8');
fclose(fid2);

color=imread('data/pepper4.jpg'); 
cmodel=color(:,:,:);
fid2=fopen('data/raw/pepper4.raw','w+');
cnt=fwrite(fid2,cmodel,'uint8');
fclose(fid2);

color=imread('data/pepper5.jpg'); 
cmodel=color(:,:,:);
fid2=fopen('data/raw/pepper5.raw','w+');
cnt=fwrite(fid2,cmodel,'uint8');
fclose(fid2);