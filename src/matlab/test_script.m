addpath('functions/');

result(1)  = pso_test('rastrigin', 10,  2, 0.001, 100,  1000);
result(2)  = pso_test('rastrigin', 20,  2, 0.001, 100,  1000);
result(3)  = pso_test('rastrigin', 40,  2, 0.001, 100,  1000);
result(4)  = pso_test('rastrigin', 60,  2, 0.001, 100,  1000);
result(5)  = pso_test('rastrigin', 80,  2, 0.001, 100,  1000);
result(6)  = pso_test('rastrigin', 100, 2, 0.001, 100,  1000);

result(7)  = pso_test('rastrigin', 10,  2, 0.001, 100,  1000);
result(8)  = pso_test('rastrigin', 10,  2, 0.001, 200,  1000);
result(9)  = pso_test('rastrigin', 10,  2, 0.001, 400,  1000);
result(10) = pso_test('rastrigin', 10,  2, 0.001, 600,  1000);
result(11) = pso_test('rastrigin', 10,  2, 0.001, 800,  1000);
result(12) = pso_test('rastrigin', 10,  2, 0.001, 1000, 1000);

plot((1:6), [result(1:6).success_rate],  'b', ...
     (1:6), [result(7:12).success_rate], 'r')
legend('increaing agents count', 'increasing max iterations')