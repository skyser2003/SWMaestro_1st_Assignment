using System;
using System.Collections.Generic;

public class Logic {
    public int Width { get; private set; }
    public int Height { get; private set; }

    private Block[,] map;

    public List<Block> BlockList;

    public Block[,] Map { get { return map; } }

    public Random random;

    public void Init(int width, int height)
    {
        Width = width;
        Height = height;

        map = new Block[Width, Height];
        BlockList = new List<Block>();

        random = new Random();

        AddRandom();
        AddRandom();
    }

    public void Add(int x, int y)
    {
        Add(x, y, 1);
    }

    public void Add(int x, int y, int value)
    {
        var block = new Block(value);
        block.X = x;
        block.Y = y;

        map[x, y] = block;
        BlockList.Add(block);
    }

    public void AddRandom()
    {
        if (BlockList.Count == Width * Height) {
            UnityEngine.Debug.Log("Full");
            return;
        }

        while (true) {
            int x = random.Next(Width);
            int y = random.Next(Height);

            if (map[x, y] == null) {
                int value = random.Next(1, 3) * 2;
                Add(x, y, value);
                UnityEngine.Debug.Log("Random block added");
                break;
            }
        }
    }

    public bool IsGameEnd()
    {
        if (BlockList.Count != Width * Height) {
            return false;
        }

        int[] xRange = { -1, 0, 1 };
        int[] yRange = { -1, 0, 1 };

        foreach (var block in BlockList) {
            foreach (int x in xRange) {
                foreach (int y in yRange) {
                    if (x == 0 && y == 0) {
                        continue;
                    }

                    int nearX = block.X + x;
                    int nearY = block.Y + y;

                    if (IsInRange(nearX, nearY) == false) {
                        continue;
                    }

                    var nearBlock = map[nearX, nearY];
                    if (nearBlock == null) {
                        continue;
                    }

                    if (nearBlock.Value == block.Value) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    public bool Move(int x, int y)
    {
        x = Math.Sign(x);
        y = Math.Sign(y);

        var mergeLineList = DoMerge(x, y);
        return AlignAfterMerge(x, y, mergeLineList);
    }

    private Dictionary<Vec2, List<MergeBlock>> DoMerge(int x, int y)
    {
        Dictionary<Vec2, List<MergeBlock>> mergeLineList = new Dictionary<Vec2, List<MergeBlock>>();

        int deltaX = -x;
        int deltaY = -y;

        int startX = 0;
        int startY = 0;
        int endX = 0;
        int endY = 0;

        if (x == 1) {
            startX = Width - 1;
            endX = -1;
        }
        else if (x == -1) {
            startX = 0;
            endX = Width;
        }

        if (y == 1) {
            startY = Height - 1;
            endY = -1;
        }
        else if (y == -1) {
            startY = 0;
            endY = Height;
        }

        Action<int, int> findMergeList = (i, j) => {
            var mergeList = new List<MergeBlock>();
            mergeLineList.Add(new Vec2(i, j), mergeList);

            MergeBlock lastMerge = null;

            for (; IsInRange(i, j); i += deltaX, j += deltaY) {
                var block = map[i, j];
                if (block == null) {
                    continue;
                }

                if (lastMerge == null) {
                    lastMerge = new MergeBlock();
                    lastMerge.Add(block);
                }
                else if (lastMerge.First.Value != block.Value) {
                    mergeList.Add(lastMerge);

                    lastMerge = new MergeBlock();
                    lastMerge.Add(block);
                }
                else if (lastMerge.IsFull() == false) {
                    lastMerge.Add(block);
                    mergeList.Add(lastMerge);

                    lastMerge = null;
                }
            }

            if (lastMerge != null) {
                mergeList.Add(lastMerge);
            }
        };

        // Horizontal
        if (x != 0 && y == 0) {
            for (int i = 0; i < Height; ++i) {
                findMergeList(startX, i);
            }
        }
        // Vertical
        else if (x == 0 && y != 0) {
            for (int i = 0; i < Width; ++i) {
                findMergeList(i, startY);
            }
        }
        // Diagonal
        else {
            int localDeltaX = -deltaX;

            int localStartX = endX - deltaX;
            int localEndX = startX - deltaX;

            int i = localStartX;
            int j = startY;

            while (true) {
                findMergeList(i, j);

                if (i != localEndX - localDeltaX) {
                    i += localDeltaX;
                }
                else if (j != endY - deltaY) {
                    j += deltaY;
                }
                else {
                    break;
                }
            }
        }

        // Merge
        foreach (var pair in mergeLineList) {
            foreach (var merge in pair.Value) {
                merge.Merge();
            }
        }

        return mergeLineList;
    }

    private bool AlignAfterMerge(int x, int y, Dictionary<Vec2, List<MergeBlock>> mergeLineList)
    {
        int deltaX = -x;
        int deltaY = -y;

        var prevMap = (Block[,])map.Clone();

        // Clear
        for (int i = 0; i < Width; ++i) {
            for (int j = 0; j < Height; ++j) {
                map[i, j] = null;
            }
        }

        BlockList.Clear();

        // Reset map
        foreach (var pair in mergeLineList) {
            var endPoint = pair.Key;
            var mergeList = pair.Value;

            int newX = endPoint.X;
            int newY = endPoint.Y;

            foreach (var merge in mergeList) {
                Reposition(merge.First, newX, newY);
                BlockList.Add(merge.First);

                newX += deltaX;
                newY += deltaY;
            }
        }

        // Check if changed
        for (int i = 0; i < Width; ++i) {
            for (int j = 0; j < Height; ++j) {
                var prevBlock = prevMap[i, j];
                var newBlock = map[i, j];

                if (prevBlock == null && newBlock == null) {
                    continue;
                }
                if (prevBlock == null || newBlock == null) {
                    return true;
                }
                if (prevBlock.Value != newBlock.Value) {
                    return true;
                }
            }
        }

        return false;
    }

    public void Reposition(Block block, int newX, int newY)
    {
        block.X = newX;
        block.Y = newY;
        map[block.X, block.Y] = block;
    }

    public bool IsInRange(int x, int y)
    {
        return 0 <= x && x < Width && 0 <= y && y < Height;
    }
}
