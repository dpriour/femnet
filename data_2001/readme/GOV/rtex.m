clear
fid = fopen ("rtex.txt", "r");
   nb=13;
  for i = 1 : nb
    m_kg(i) = fscanf(fid,"%f",1);
    Rtex(i) = fscanf(fid,"%f",1);
    diam(i) = fscanf(fid,"%f",1);
    A(i) = fscanf(fid,"%f",1);
    B(i) = fscanf(fid,"%f",1);
    plot(Rtex,diam);
    xlabel("Rtex g/Km");
    ylabel("Diameter mm");
  end
fclose (fid);

