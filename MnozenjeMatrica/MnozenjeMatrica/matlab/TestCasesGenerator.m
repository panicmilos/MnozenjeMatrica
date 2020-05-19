% Generisanje random dimenzija
n1 = randi([1, 1000])
n2 = randi([1, 1000])
n3 = randi([1, 1000])
% Generisanje radnom elemenata matrica sa prethodno dobijenim dimenzijama
A = randi([-10, 10], [n1,n2]);
B = randi([-10, 10], [n2,n3]);
% Otvaranje toka
fid = fopen( 'TestCase5.txt', 'w' );
% Upis matrice A
[n, m] = size(A);      
fprintf(fid, '[%d,%d]\n', n, m);
 for i=1:n
   for j=1:m
     fprintf( fid, '%d', A(i,j));
     if j ~= m
         fprintf(fid, ' ');
     end
   end
   if i == n && j == m
       fprintf(fid, ';');
   end
   fprintf(fid,'\n');
 end
 % Upis matrice B
[n, m] = size(B);      
fprintf(fid, '[%d,%d]\n', n, m);
 for i=1:n
   for j=1:m
     fprintf( fid, '%d', B(i,j));
     if j ~= m
         fprintf(fid, ' ');
     end
   end
   if i == n && j == m
       fprintf(fid, ';');
   end
   fprintf(fid,'\n');
 end
 % Dobijanje rezultata
 C = A * B;
 % Upis matrice C
[n, m] = size(C);      
fprintf(fid, '[%d,%d]\n', n, m);
 for i=1:n
   for j=1:m
     fprintf( fid, '%d', C(i,j));
     if j ~= m
         fprintf(fid, ' ');
     end
   end
   if i == n && j == m
       fprintf(fid, ';');
   end
   fprintf(fid,'\n');
 end
 % Zatvaranje toka
 fclose(fid);

 
