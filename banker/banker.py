class Resource():

    def __init__(self, availableRS, allocationRS, maxRS):
        self.availableRS = availableRS
        self.allocationRS = allocationRS
        self.remainNeedRS = [[] for _ in range(len(allocationRS))]
        self.maxRS = maxRS

    def printRS(self):
        print("Available Resource:", *self.availableRS)
        for i in range(len(self.allocationRS)):
            print("Process", i, self.allocationRS[i], self.maxRS[i], self.remainNeedRS[i])

    def initSystem(self):  
        for i in range(len(self.allocationRS)):
            for j in range(len(self.allocationRS[i])):
                self.remainNeedRS[i].append(self.maxRS[i][j] - self.allocationRS[i][j])
                self.availableRS[j] -= self.allocationRS[i][j]
        self.printRS()

    def CanGive(self, want, available):
        for i in range(len(want)):
            if (want[i] > available[i]):
                return False
        return True

    def safty(self):
        allocationRS = [ x[:] for x in self.allocationRS]
        remainNeedRS = [ x[:] for x in self.remainNeedRS]
        maxRS = [x[:] for x in self.maxRS]
        availableRS = self.availableRS[:]
        no = [i for i in range(len(self.allocationRS))]
        saftyList = []
        while(len(allocationRS)):
            findRS = False
            i = 0
            while  i < len(remainNeedRS):
                if self.CanGive(remainNeedRS[i], availableRS):
                    findRS = True
                    saftyList.append(no[i])
                    for j in range(len(availableRS)):
                        availableRS[j] += allocationRS[i][j]
                    maxRS.remove(maxRS[i])
                    allocationRS.remove(allocationRS[i])
                    remainNeedRS.remove(remainNeedRS[i])
                    no.remove(no[i])
                    break
                i += 1
            if findRS is False:
                print("Can't find Safe sequence")
                return False
        print("find Safe sequence :", saftyList)
        return True

    def requestMore(self):
        print("=================================")
        print("Resource request algorithm start")
        while (True):
            self.printRS()
            continueornot = input("start or not (Y or n)")
            if continueornot == 'n' or continueornot == 'N':
                break
            no = int(input("process no:  "))
            moreResource = [int(input("resource #%d:  " % i)) for i in range(len(self.availableRS))]
            if self.CanGive(moreResource, self.availableRS) is False:
                print("Do not gant, available no more than you want")
                continue
            for i in range(len(self.availableRS)):
                self.allocationRS[no][i] += moreResource[i]
                self.remainNeedRS[no][i] -= moreResource[i]
                self.availableRS[i] -= moreResource[i]
            self.printRS()
            if self.safty() is False:
                print("Do not gant, unsafe, restore to origin")
                for i in range(len(self.availableRS)):
                    self.allocationRS[no][i] -= moreResource[i]
                    self.remainNeedRS[no][i] += moreResource[i]
                    self.availableRS[i] += moreResource[i]
            print("=================================")


def main():
    availableRS = [10, 5, 7]
    allocationRS = [[0, 1, 0], [2, 0, 0], [3, 0, 2], [2, 1, 1], [0, 0, 2]]
    maxRS = [[7, 5, 3], [3, 2, 2],[9, 0, 2], [2, 2, 2], [4, 3, 3]]
    banker = Resource(availableRS, allocationRS, maxRS)
    banker.initSystem()
    banker.safty()
    banker.requestMore()

if __name__ == "__main__":
    main()