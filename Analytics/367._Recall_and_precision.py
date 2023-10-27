import re

def is_valid_license_plate(plate):
    # Регулярное выражение для проверки номеров
    pattern = r'^[2-46-9]-\d{4}(BIG|BAG|BUG|BG|UG)$'
    pattern5 = r'^5-\d{4}(BUG|BG|UG)$'

    # Проверяем соответствие номера паттерну.
    return bool(re.match(pattern, plate)) or bool(re.match(pattern5, plate))

n, k = map(int, input().split())

TP = 0  # Количество номеров, которые верно распознаны как большегрузные
FN = 0  # Количество номеров, которые неверно распознаны как легковые
FP = 0  # Количество номеров, которые неверно распознаны как большегрузные

for i in range(n):
    plate = input()
    
    if is_valid_license_plate(plate):   # Если номер большегрузного автомобиля
        TP += 1
    else:
        FN += 1

for i in range(k):
    plate = input()
    
    if is_valid_license_plate(plate):   # Если номер большегрузного автомобиля
        FP += 1

precision = TP / (TP + FP)
recall = TP / (TP + FN)

print(recall, precision)
