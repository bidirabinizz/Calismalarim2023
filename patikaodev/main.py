import math

# Noktaların tanımlanmasını yaptım
points = [(1, 2), (4, 6), (7, 8), (2, 1), (3, 5)]

# Öklid mesafesi hesaplayan fonksiyonu yazdım internetten araştırarak
def euclideanDistance(point1, point2):
    return math.sqrt((point2[0] - point1[0]) ** 2 + (point2[1] - point1[1]) ** 2)

distances = []
for i in range(len(points)):
    for j in range(i + 1, len(points)):
        distance = euclideanDistance(points[i], points[j])
        distances.append(distance)

# Minimum mesafeyi bulmak için yazdım
min_distance = min(distances)

# Sonucu konsola yazdırma
print(f"Noktalar arasındaki minimum mesafe: {min_distance}")
