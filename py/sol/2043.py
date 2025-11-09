#! /usr/bin/python3
from include.leetcode_structs import *


class Bank:

    def __init__(self, balance: list[int]):
        self.balance:list[int]  = balance
        self.accounts: int = len(balance)

    def transfer(self, account1: int, account2: int, money: int) -> bool:
        if not 0<=account1 -1< self.accounts or not 0<=account2-1<self.accounts:
            return False
        elif money > self.balance[account1-1]:
            return False
        
        self.balance[account1-1] -= money
        self.balance[account2-1] += money

        return True


    def deposit(self, account: int, money: int) -> bool:
        if 0<=account-1<self.accounts:
            self.balance[account-1] += money
            return True
        return False
        

    def withdraw(self, account: int, money: int) -> bool:
        if 0<=account-1<self.accounts and money <= self.balance[account-1]:
            self.balance[account-1] -= money
            return True

        return False
        



if __name__ == "__main__":
    S= Solution()
    l = boxGrid = [[2,6],[1,3],[8,10],[15,18]]
    r = S.merge(l)
    print(r)
    
