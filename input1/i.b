{$inline on}
{$M $FFFFFFF,0}
{$optimization on}
const	maxn=20;
	delx:array[1..7]of longint=(-1,0,1,0,-1,0,1);
	dely:array[1..7]of longint=(0,-1,0,1,0,-1,0);
var	state,data,color,tstate,tdata,tcolor,
	dtstate,dtdata,dtcolor,cod:array[1..maxn,1..maxn]of longint;
	tcount,dtcount,count:array[1..maxn*maxn]of longint;
	sure,tsure,dtsure:array[1..maxn,1..maxn]of boolean;
	q:array[1..maxn*maxn]of record x,y,d:longint; unique:boolean; end;
	loc:array[1..maxn*maxn]of record x,y:longint; end;
	tvs,vs:array[1..maxn,1..maxn]of boolean;
	n,m,max,h,t,tloc,i,j:longint;

procedure out(); inline;
var	i,j:longint;
begin
for i:=1 to n do
	begin
	for j:=1 to m do
		if not sure[i][j]
			then write('?')
		else if state[i][j]=2
			then write('#')
		else if data[i][j]>0
			then write(data[i][j])
			else write('.');
	writeln;
	end;
writeln;
end;

function finalcheck():boolean; //inline;
var	i,j,k,nx,ny,tx,ty,tt,checktt:longint;
begin
for i:=1 to n-1 do
	for j:=1 to m-1 do
		begin
		if (state[i][j]=2)and(state[i+1][j+1]=2)
		and(state[i][j+1]=2)and(state[i+1][j]=2)
			then exit(false);
		end;
for i:=1 to n do
	begin
	for j:=1 to m do
		if state[i][j]=2 then break;
	if state[i][j]=2 then break;
	end;
h:=1; t:=1;
q[1].x:=i; q[1].y:=j;
fillchar(vs,sizeof(vs),0);
vs[i][j]:=true;
while h<=t do
	begin
	nx:=q[h].x;
	ny:=q[h].y;
	for k:=1 to 4 do
		begin
		tx:=nx+delx[k];
		ty:=ny+dely[k];
		if (tx<1)or(tx>n)
		or (ty<1)or(ty>m)or vs[tx][ty]
			then continue;
		vs[tx][ty]:=true;
		if state[tx][ty]=2
			then begin
			inc(t);
			q[t].x:=tx; q[t].y:=ty;
			end;
		end;
	inc(h);
	end;
for i:=1 to n do
	for j:=1 to m do
		if (state[i][j]=2)and not vs[i][j]
			then exit(false);
fillchar(vs,sizeof(vs),0);
for i:=1 to n do
	for j:=1 to m do
		if not vs[i][j] and (state[i][j]=1)
			then begin
			h:=1; t:=1;
			q[1].x:=i; q[1].y:=j;
			vs[i][j]:=true;
			tt:=1; checktt:=-1;
			if data[i][j]>0 then checktt:=data[i][j];
			while h<=t do
				begin
				nx:=q[h].x;
				ny:=q[h].y;
				for k:=1 to 4 do
					begin
					tx:=nx+delx[k];
					ty:=ny+dely[k];
					if (tx<1)or(tx>n)or(ty<1)or(ty>m)
					or vs[tx][ty] or (state[tx][ty]=2)
						then continue;
					vs[tx][ty]:=true;
					inc(t);
					q[t].x:=tx; q[t].y:=ty;
					if data[tx][ty]>0 then checktt:=data[tx][ty];
					inc(tt);
					end;
				inc(h);
				end;
			if checktt<>tt then exit(false);
			end;
finalcheck:=true;
end;

function nowcheck():boolean; //inline;
var	k,nx,ny,tx,ty,i,j,tt,checktt:longint;
	flag:boolean;
begin
for i:=1 to n-1 do
	for j:=1 to m-1 do
		begin
		if (state[i][j]=2)and(state[i+1][j+1]=2)
		and(state[i][j+1]=2)and(state[i+1][j]=2)
			then exit(false);
		end;
for i:=1 to tloc do
	if count[i]>data[loc[i].x][loc[i].y]
		then exit(false);
fillchar(vs,sizeof(vs),0);
for i:=1 to n do
	for j:=1 to m do
		if not vs[i][j] and (state[i][j]=1)and(color[i][j]>0)
			then begin
			h:=1; t:=1;
			q[1].x:=i; q[1].y:=j;
			vs[i][j]:=true;
			tt:=1; checktt:=data[loc[color[i][j]].x][loc[color[i][j]].y];
			flag:=false;
			while h<=t do
				begin
				nx:=q[h].x;
				ny:=q[h].y;
				for k:=1 to 4 do
					begin
					tx:=nx+delx[k];
					ty:=ny+dely[k];
					if (tx<1)or(tx>n)or(ty<1)or(ty>m)
					or vs[tx][ty] or sure[tx][ty] and(state[tx][ty]=2)
						then continue;
					if not sure[tx][ty]
						then begin
						flag:=true;
						continue;
						end;
					if (color[tx][ty]<>0)and(color[tx][ty]<>color[i][j])
						then exit(false);
					vs[tx][ty]:=true;
					inc(t);
					q[t].x:=tx; q[t].y:=ty;
					inc(tt);
					end;
				inc(h);
				end;
			if not flag
				then if checktt<>tt
					then exit(false)
					else
				else if checktt<tt
					then exit(false);
			end;
tt:=0;
checktt:=0;
fillchar(vs,sizeof(vs),0);
for i:=1 to n do
	for j:=1 to m do
		if not vs[i][j] and sure[i][j] and(state[i][j]=2)
			then begin
			h:=1; t:=1;
			q[1].x:=i; q[1].y:=j;
			fillchar(vs,sizeof(vs),0);
			vs[i][j]:=true;
			flag:=false;
			while h<=t do
				begin
				nx:=q[h].x;
				ny:=q[h].y;
				for k:=1 to 4 do
					begin
					tx:=nx+delx[k];
					ty:=ny+dely[k];
					if (tx<1)or(tx>n)
					or (ty<1)or(ty>m)or vs[tx][ty]
						then continue;
					if not sure[tx][ty]
						then begin
						flag:=true;
						//break;
						end;
					if state[tx][ty]=2
						then begin
						inc(t);
						q[t].x:=tx; q[t].y:=ty;
						vs[tx][ty]:=true;
						end;
					end;
				//if flag then break;
				inc(h);
				end;
			inc(checktt);
			if not flag then inc(tt);
			end;
if (checktt>1)and(tt=1)or(tt>1) then exit(false);
nowcheck:=true;
end;

function deducecheck():boolean; inline;
var	i,j:longint;
	c:boolean;
begin
c:=true;
for i:=1 to n do
	for j:=1 to m do
		c:=c and (dtsure[i][j]=sure[i][j]);
for i:=1 to n do
	for j:=1 to m do
		c:=c and (dtstate[i][j]=state[i][j]);
for i:=1 to n do
	for j:=1 to m do
		c:=c and (dtcolor[i][j]=color[i][j]);
for i:=1 to tloc do
	c:=c and (dtcount[i]=count[i]);
deducecheck:=c;
end;
procedure deducebackup(); inline;
begin
dtsure:=sure;
dtstate:=state;
dtcolor:=color;
dtcount:=count;
end;
procedure deduce();
var	rx,ry,lx,ly,c,i,j,k,last,tt,
	ax,ay,bx,by,cx,cy,dx,dy,nx,ny,tx,ty,tag:longint;
	flag,bool,temp:boolean;
begin
//writeln('********');
//out();
repeat
	deducebackup();
	
	//Since two islands may only touch at corners,
	//cells between two partial islands
	//(numbers and adjacent white cells that don't total their numbers yet)
	//must be black. This is often how to start a Nurikabe puzzle,
	//by marking cells adjacent to two or more numbers as black.
	
	for i:=1 to n do
		for j:=1 to m do
			if not sure[i][j]
				then begin
				last:=-1; tt:=0;
				for k:=1 to 4 do
					begin
					cx:=i+delx[k];
					cy:=j+dely[k];
					if (cx<1)or(cx>n)or(cy<1)or(cy>m)
						then continue;
					if sure[cx][cy] and (state[cx][cy]=1)
					and(color[cx][cy]<>0)and(color[cx][cy]<>last)
						then begin
						inc(tt);
						last:=color[cx][cy];
						end;
					end;
				if tt>=2
					then begin
					sure[i][j]:=true;
					state[i][j]:=2;
					end;
				end;
	
	//All white cells must eventually be part of exactly one island.
	//If there is a white region that does not contain a number,
	//and there is no possible way for it to connect to a numbered white region,
	//the sole connecting pathway must be black.
	
	for i:=1 to n do
		for j:=1 to m do
			if not sure[i][j]
				then begin
				ax:=i+delx[1]; ay:=j+dely[1];
				bx:=i+delx[2]; by:=j+dely[2];
				cx:=i+delx[3]; cy:=j+dely[3];
				dx:=i+delx[4]; dy:=j+dely[4];
				if  ((ax<1)or(ax>n)or(ay<1)or(ay>m) or sure[ax][ay]and(state[ax][ay]=2))
				and ((bx<1)or(bx>n)or(by<1)or(by>m) or sure[bx][by]and(state[bx][by]=2))
				and ((cx<1)or(cx>n)or(cy<1)or(cy>m) or sure[cx][cy]and(state[cx][cy]=2))
				and ((dx<1)or(dx>n)or(dy<1)or(dy>m) or sure[dx][dy]and(state[dx][dy]=2))
			       		then begin
					sure[i][j]:=true;
					state[i][j]:=2;
					end;
				end;
	
	//Once an island is "complete"  that is,
	//it has all the white cells its number requires  
	//all cells that share a side with it must be black.
	//Obviously, any cells marked with '1' at the outset are complete islands
	//unto themselves, and can be isolated with black at the beginning.
	
	fillchar(vs,sizeof(vs),false);
	for i:=1 to tloc do
		if (data[loc[i].x][loc[i].y]>0)and(count[i]=data[loc[i].x][loc[i].y])
			then begin
			h:=1; t:=1;
			q[1].x:=loc[i].x;
			q[1].y:=loc[i].y;
			vs[q[1].x][q[1].y]:=true;
			while h<=t do
				begin
				nx:=q[h].x;
				ny:=q[h].y;
				for k:=1 to 4 do
					begin
					tx:=nx+delx[k];
					ty:=ny+dely[k];
					if (tx<1)or(tx>n)or(ty<1)or(ty>m)
					or vs[tx][ty] or sure[tx][ty] and (state[tx][ty]=2)
						then continue;
					if color[tx][ty]=i
						then begin
						inc(t);
						q[t].x:=tx; q[t].y:=ty;
						vs[tx][ty]:=true;
						end
						else begin
						sure[tx][ty]:=true;
						state[tx][ty]:=2;
						end;
					end;
				inc(h);
				end;
			end;
	
	//Whenever three black cells form an "elbow"  an L-shape  the cell in the bend
	//(diagonally in from the corner of the L) must be white.
	//(The alternative is a "pool", for lack of a better term.)
	
	for i:=1 to n do
		for j:=1 to m do
			if not sure[i][j]
				then begin
				if  (i>1)and(j>1)and sure[i-1][j-1] and(state[i-1][j-1]=2)
				and sure[i][j-1] and(state[i][j-1]=2)and sure[i-1][j] and(state[i-1][j]=2)
				       then begin
			 		sure[i][j]:=true;
			 		state[i][j]:=1;
					color[i][j]:=0;
			       		continue;
					end;
				if  (i>1)and(j<m)and sure[i-1][j+1] and(state[i-1][j+1]=2)
				and sure[i][j+1] and(state[i][j+1]=2)and sure[i-1][j] and(state[i-1][j]=2)
					then begin
					sure[i][j]:=true;
					state[i][j]:=1;
					color[i][j]:=0;
					continue;
					end;
				if  (i<n)and(j>1)and sure[i+1][j-1] and(state[i+1][j-1]=2)
				and sure[i][j-1] and(state[i][j-1]=2)and sure[i+1][j] and(state[i+1][j]=2)
					then begin
					sure[i][j]:=true;
					state[i][j]:=1;
					color[i][j]:=0;
					continue;
					end;
				if  (i<n)and(j<m)and sure[i+1][j+1] and(state[i+1][j+1]=2)
				and sure[i][j+1] and(state[i][j+1]=2)and sure[i+1][j] and(state[i+1][j]=2)
					then begin
					sure[i][j]:=true;
					state[i][j]:=1;
					color[i][j]:=0;
					end;
				end;
	
	//All white cells must eventually be part of exactly one island.
	//If there is a white region that does not contain a number,
	//and there is only one possible way for it to connect to a numbered white region,
	//the sole connecting pathway must be white.
	
	fillchar(vs,sizeof(vs),false);
	for i:=1 to n do
		for j:=1 to m do
			if sure[i][j]and(state[i][j]=1)and(color[i][j]>0)
				then begin
				h:=1; t:=1;
				q[1].x:=i; q[1].y:=j;
				q[1].d:=0; q[1].unique:=true;
				fillchar(tvs,sizeof(tvs),false);
				tvs[i][j]:=true; vs[i][j]:=true;
				while h<=t do
					begin
					nx:=q[h].x;
					ny:=q[h].y;
					tt:=0; tag:=-1;
					for k:=1 to 4 do
						begin
						tx:=nx+delx[k];
						ty:=ny+dely[k];
						if (tx<1)or(tx>n)or(ty<1)or(ty>m)
						or tvs[tx][ty] or sure[tx][ty] and (state[tx][ty]=2)
							then continue;
						flag:=false;
						for c:=1 to 4 do
							begin
							cx:=tx+delx[c];
							cy:=ty+dely[c];
							if (cx<1)or(cx>n)or(cy<1)or(cy>m)
								then continue;
							if sure[cx][cy] and (state[cx][cy]=1)
							and (color[tx][ty]<>0)and(color[cx][cy]<>cod[i][j])
								then begin
								flag:=true;
								break;
								end;
							end;
						if flag then continue;
						if q[h].d+1<=data[loc[color[i][j]].x][loc[color[i][j]].y]-count[color[i][j]]
							then begin
							inc(t);
							q[t].x:=tx; q[t].y:=ty;
							q[t].d:=q[h].d+1;
							q[t].unique:=false;
							tvs[tx][ty]:=true; vs[tx][ty]:=true;
							inc(tt); tag:=t;
							end;
						end;
					{if (q[h].unique)and(tt=1)and(state[q[tag].x][q[tag].y]=1)
					and(color[q[tag].x][q[tag].y]=0)
						then begin
						q[tag].unique:=true;
						sure[q[tag].x][q[tag].y]:=true;
						state[q[tag].x][q[tag].y]:=1;
						color[q[tag].x][q[tag].y]:=color[i][j];
						inc(count[color[i][j]]);
						end;}
					inc(h);
					end;
				end;
	
	//Some puzzles will require the location of "unreachables"  
	//cells that cannot be connected to any number,
	//being either too far away from all of them or blocked by other numbers.
	//Such cells must be black.
	//Often, these cells will have only one route of connection to other black cells
	//or will form an elbow whose required white cell
	//(see previous bullet) can only reach one number, allowing further progress.
	//!
	
	for i:=1 to n do
		for j:=1 to m do
			if not vs[i][j]
				then begin
				sure[i][j]:=true;
				state[i][j]:=2;
				end;
	
	//If an island of size N already has N-1 white cells identified,
	//and there are only two remaining cells to choose from, and those two cells touch at their corners,
	//then the cell between those two that is on the far side of the island must be black.
	
	for i:=1 to n do
		for j:=1 to m do
			if (data[i][j]=2)and(count[cod[i][j]]=1)
				then begin
				for k:=1 to 4 do
					begin
					ax:=i+delx[k]; ay:=j+dely[k];
					bx:=i+delx[k+1]; by:=j+dely[k+1];
					cx:=i+delx[k+2]; cy:=j+dely[k+2];
					dx:=i+delx[k+3]; dy:=j+dely[k+3];
					if  ((ax<1)or(ax>n)or(ay<1)or(ay>m)or 
					sure[ax][ay]and((state[ax][ay]=1)and
					(color[ax][ay]=color[i][j]) or (state[ax][ay]=2)))
					and ((bx<1)or(bx>n)or(by<1)or(by>m)or 
					sure[bx][by]and((state[bx][by]=1)and
					(color[bx][by]=color[i][j]) or (state[bx][by]=2)))
						then if (cx>=1)and(cx<=n)and(dy>=1)and(dy<=m)and not sure[cx][dy]
							then begin
							sure[cx][dy]:=true;
							state[cx][dy]:=2;
							break;
							end;
					end;
				end;
	
	//All white cells must eventually be part of exactly one island.
	//If there is a white region that does not contain a number,
	//and there is only one possible number for it to connect to a numbered white region,
	//the white cells must be in that numbered white region.
	
	fillchar(vs,sizeof(vs),false);
	for i:=1 to n do
		for j:=1 to m do
			if sure[i][j] and (state[i][j]=1) and (color[i][j]=0)
				then begin
				h:=1; t:=1;
				q[1].x:=i; q[1].y:=j;
				q[1].d:=0; tt:=0;
				vs[i][j]:=true; c:=-1;
				while h<=t do
					begin
					nx:=q[h].x;
					ny:=q[h].y;
					for k:=1 to 4 do
						begin
						tx:=nx+delx[k];
						ty:=ny+dely[k];
						if (tx<1)or(tx>n)or(ty<1)or(ty>m)
						or vs[tx][ty] or sure[tx][ty] and (state[tx][ty]=2)
							then continue;
						inc(t);
						q[t].x:=tx; q[t].y:=ty; q[t].d:=q[h].d+1;
						vs[tx][ty]:=true;
						if sure[tx][ty] and(state[tx][ty]=1)and(color[tx][ty]>0)
							then begin
							if data[loc[color[tx][ty]].x][loc[color[tx][ty]].y]
							-count[color[tx][ty]]>=q[t].d
								then begin
								if c<>color[tx][ty]
									then inc(tt);
								c:=color[tx][ty];
								end;
							end;
						end;
					inc(h);
					end;
				if (tt=1)
				       	then begin
				       	color[i][j]:=c;
				       	inc(count[c]);
				       	end;
				end;
	
	//All black cells must eventually be connected.
	//If there is a black region with only one possible way to connect to the rest of the board,
	//the sole connecting pathway must be black.
	
	tt:=0; rx:=-1; ry:=-1; temp:=false;
	fillchar(vs,sizeof(vs),0);
	for i:=1 to n do
		for j:=1 to m do
			if not vs[i][j] and sure[i][j] and(state[i][j]=2)
				then begin
				h:=1; t:=1;
				q[1].x:=i; q[1].y:=j;
				fillchar(vs,sizeof(vs),0);
				vs[i][j]:=true;
				flag:=false; bool:=false;
				while h<=t do
					begin
					nx:=q[h].x;
					ny:=q[h].y;
					for k:=1 to 4 do
						begin
						tx:=nx+delx[k];
						ty:=ny+dely[k];
						if (tx<1)or(tx>n)
						or (ty<1)or(ty>m)or vs[tx][ty]
							then continue;
						if not sure[tx][ty]
							then begin
							if flag
								then bool:=true
								else begin
								lx:=rx; ly:=ry;
								rx:=tx; ry:=ty;
								flag:=true;
								end;
							end;
						if state[tx][ty]=2
							then begin
							inc(t);
							q[t].x:=tx; q[t].y:=ty;
							vs[tx][ty]:=true;
							end;
						end;
					inc(h);
					end;
				inc(tt);
				if temp and(lx<>-1)
					then begin
					sure[lx][ly]:=true;
					state[lx][ly]:=2;
					end;
				temp:=not bool and flag;
				end;
	if temp and(lx<>-1) and(tt>1)
		then begin
		sure[rx][ry]:=true;
		state[lx][ly]:=2;
		end;
	
	until deducecheck();
//out();
//writeln('********');
end;

procedure dfs(dep:longint);
var	i,j,nx,ny:longint;
	tstate,tcolor:array[1..maxn,1..maxn]of longint;
	tcount:array[1..maxn*maxn]of longint;
	tsure:array[1..maxn,1..maxn]of boolean;
	procedure backup(); inline;
	begin
	tsure:=sure;
	tstate:=state;
	tcolor:=color;
	tcount:=count;
	end;
	procedure restore(); inline;
	begin
	sure:=tsure;
	state:=tstate;
	color:=tcolor;
	count:=tcount;
	end;
begin
{if dep>max
	then begin
	writeln(dep);
	max:=dep;
	end;}
backup();
deduce();
if not nowcheck()
	then begin
	restore();
	exit;
	end;
dep:=dep;
if dep>tloc
	then begin
	if finalcheck()
		then begin
		for i:=1 to n do
			begin
			for j:=1 to m do
				if data[i][j]<>0
					then write(data[i][j],' ')
				else if state[i][j]=1
					then write('. ')
					else write('# ');
			writeln;
			end;
		//writeln;
		close(input); close(output);
		halt;
		end;
	end
	else begin
	nx:=loc[dep].x;
	ny:=loc[dep].y;
	if sure[nx][ny]
		then dfs(dep+1)
		else begin
		for i:=2 downto 1 do
			begin
			state[nx][ny]:=i;
			sure[nx][ny]:=true;
			if nowcheck() then dfs(dep+1);
			state[nx][ny]:=0;
			sure[nx][ny]:=false;
			end;
		end;
	end;
restore();
end;

begin
assign(input,'Nurikabe.in'); reset(input);
assign(output,'Nurikabe.out'); rewrite(output);
readln(n,m);
for i:=1 to n do
	begin
	for j:=1 to m do
		read(data[i][j]);
	readln;
	end;
tloc:=0;
for i:=1 to n do
	for j:=1 to m do
		begin
		inc(tloc);
		cod[i][j]:=tloc;
		loc[tloc].x:=i;
		loc[tloc].y:=j;
		end;
for i:=1 to n do
	for j:=1 to m do
		begin
		if data[i][j]=0
			then sure[i][j]:=false
			else begin
			sure[i][j]:=true;
			state[i][j]:=1;
			color[i][j]:=cod[i][j];
			count[cod[i][j]]:=1;
			end;
		end;
dfs(1);
writeln('no solution');
close(input); close(output);
end.
