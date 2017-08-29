clear;
name = 'data';
txt = strcat(name,'.txt');
gif = strcat(name, '.gif');
img = strcat(name, '.png');
size = 16;
cut = 8;
fileID = fopen(txt,'r');
formatSpec = '%f';
sizeA = [size size size];
A = fscanf(fileID,formatSpec);
fclose(fileID);

B = reshape(A, sizeA);

figure(1)
for n = 1:1:size
    I(1:size,1:size) = uint8(B(n,:,:));
    imshow(I);
    drawnow;

    frame = getframe(1);

    im = frame2im(frame);

    [imind,cm] = rgb2ind(im,256);

      if n == 1;
          imwrite(imind,cm,gif,'gif', 'Loopcount',inf);
      else
          imwrite(imind,cm,gif,'gif','WriteMode','append');
      end
end

figure(2)
J(1:size,1:size) = uint8(B(cut,:,:));
imshow(J);
imwrite(J,img);