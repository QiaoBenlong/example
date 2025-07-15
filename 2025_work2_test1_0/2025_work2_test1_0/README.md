%% 参数
Es = 1;                % 归一化符号能量
A  = sqrt(Es);         % 幅度

%% 创建三幅子图窗口
figure('Name','OOK / 2PSK / 正交2FSK 星座图','NumberTitle','off');
titles = {'OOK 星座（开/关）', '2PSK 星座（BPSK）', '正交 2FSK 星座'};
for k = 1:3
    subplot(1,3,k); grid on; hold on; axis equal;
    xlabel('I 分量'); ylabel('Q 分量');
    title(titles{k},'FontWeight','bold');
    xlim([-1.2 1.2]); ylim([-1.2 1.2]);
end

%% 1) OOK：{0, +A} 仅在 I 轴
subplot(1,3,1);
scatter([0 A],[0 0],'filled');                % 0 -> 闭，A -> 开
text(0,0.05,'0','Horizontal','center');
text(A,0.05,'+A','Horizontal','center');

%% 2) 2PSK（BPSK）：{+A, -A} 仍在 I 轴
subplot(1,3,2);
scatter([-A A],[0 0],'filled');
text(-A,0.05,'-A','Horizontal','center');
text( A,0.05,'+A','Horizontal','center');

%% 3) 正交 2FSK：两个点位于正交坐标 (A,0) 与 (0,A)
subplot(1,3,3);
scatter([A 0],[0 A],'filled');
text(A,0.05,'(A,0)','Horizontal','center');
text(0,A+0.05,'(0,A)','Horizontal','center');

