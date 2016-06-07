%% Transformada de Fourier de um sinal no Tempo
% Por: Evandson Dantas (evandson@live.com / Jun-2016)
%% Reset do MatLab: Fecha Figuras e Limpa a WorkSpace

close('all');clc;

%% Par�metros de entrada
fs = 1000;             % Frequ�ncia de amostragem
tempo_maximo = 3;      % Em Segundos
fprintf('Par�metros de Entrada:\rFrequ�ncia de Amostragem: %.2f Hz\r',fs);
fprintf('Frequ�ncia M�xima:  %.2f Hz',fs/2);
fprintf('Tempo de An�lise do Sinal: %.2f segundos',tempo_maximo);
% Calculo do tempo (autom�tico)
t = 0:1/fs:tempo_maximo;

% Sinal desejado
y = cos(2*pi*30*t) + cos(2*pi*50*t) + 2*cos(2*pi*150*t);

%% Plotagem de figura
% No eixo do tempo
subplot(211);        % Subdivis�o em 1 
plot(t,y,'r-');      % Plota o sinal com cor vermelha
xlabel('Tempo (s)'); % Legenda do eixo X
ylabel('Amplitude'); % Legenda do eixo Y
title('Sinal no dom�nio do Tempo');

subplot(212);        % Subdivis�o em 2
% C�lculo dos vetores da frequ�ncias.
% Pelo teorema de Nyquist, visualizamos at� a largura de banda de fs/2
freqx= -fs/2:fs/(length(y)-1):fs/2;                % Dois lados (incluindo o eixo negativo)
% C�lculo da Transformada de Fourier com deslocamento para o centro
freqy = fftshift(fft(y));plot(freqx,abs(freqy));
xlabel('Frequ�ncia (Hz)');                         % Legenda X
ylabel('|F(\omega)|');                             % Transformada de Fourier
title('Sinal no dom�nio da Frequ�ncia')
%% 
% � poss�vel utilizar tamb�m as fun��es prontas listadas abaixo:

%fvtool(y,1,'Fs',fs);                              % M�todo mais f�cil (Filtro passa-tudo = Pr�prio Sinal)
%freqz(y,1,length(y),fs);                          % Outro m�todo mais f�cil