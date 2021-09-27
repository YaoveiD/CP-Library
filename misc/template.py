# simple input
def re(_typename: type = int):
  return map(_typename, input().split())
def rv(_typename: type = int):
  return list(re(_typename))

class Solution:
  def _solve(self) -> None:
    pass

  def solve(self) -> None:
    tt = int(input()) #1
    while tt:
      tt -= 1
      self._solve()

sol = Solution()
sol.solve()