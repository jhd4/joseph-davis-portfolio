class Cycle:
    def __init__(self, list):
        self.list = list
        self.max_element = self.get_max()
        self.min_element = self.get_min()
        self.reorder()
    
    def get_max(self):
        max_element = 0
        for a in self.list:
            max_element = max(a, max_element)
        return max_element

    def get_min(self):
        min_element = self.list[0]
        for a in self.list:
            min_element = min(a, min_element)
        return min_element

    def reorder(self):
        if len(self.list) < 2:
            return
        else:
            while(self.list[0] != self.min_element):
                self.list.append(self.list[0])
                self.list.pop(0)

    def get_index(self, n):
        for i in range(len(self.list)):
            if self.list[i] == n:
                return i
        return -1 

    def __call__(self, n):
        index_of_n = self.get_index(n)
        if index_of_n == -1:
            return n
        else:
            output_index = (index_of_n + 1) % len(self.list)
            return self.list[output_index]
    
    def __str__(self):
        output = "("
        for a in self.list:
            output += f"{a},"
        output = output[:-1] + ")"
        return output
    
    def __repr__(self):
        return self.__str__()
    

if __name__ == "__main__":
    c1 = Cycle([4, 3, 1, 2])
    c2 = Cycle([10])
    c3 = Cycle([4, 7, 9, 2, 23])
    print(c1)
    print(c2)
    print(c3)
    print(c1(1))
    print(c1(3))
    print(c1(5))
    print(c2(10))
    print(c3(23))
    print(c3(9))
    print(c3(50))