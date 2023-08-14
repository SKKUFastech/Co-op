% CSV 파일에서 데이터 읽어오기
datacommand = csvread('outputcommand.csv');
dataactual = csvread('outputactual.csv');

% 마지막 데이터 제외
datacommand = datacommand(1:end-1);
dataactual = dataactual(1:end-1);
datadiff = datacommand-dataactual

% 그래프 그리기
subplot(3,1,1)
plot(datacommand, 'b', 'DisplayName', 'Command Position');
hold on;
plot(dataactual, 'r', 'DisplayName', 'Actual Position');
hold off;
% 그래프에 제목과 축 레이블 추가
title('Position Comparison');
xlabel('Sample');
ylabel('Position Value');
grid on;
grid minor;
% 범례 추가
legend('show');

subplot(3,1,2)
plot(abs(datadiff), 'k', 'DisplayName', 'Difference');
title('Position Comparison');
xlabel('Sample');
ylabel('Position Difference (abs)');
% 그래프 표시
grid on;
grid minor;
legend('show');

subplot(3,1,3)
plot(datadiff, 'k', 'DisplayName', 'Difference');
title('Position Comparison');
xlabel('Sample');
ylabel('Position Difference');


% 범례 추가
legend('show');
grid on;
grid minor;