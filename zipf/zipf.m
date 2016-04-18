N= 100000;
exp = 1;
m = 1000000;

Data = zipf_rand(N,exp,m);
Data = Data';
disp(max(Data));
disp(min(Data));
disp(mean(Data));
fileID = fopen('B_1.txt','w');
for i = (1:m)
   curr = Data(i,:);
   fprintf(fileID,'%d\n',curr);
end
fclose(fileID);