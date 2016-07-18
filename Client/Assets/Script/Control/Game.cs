using UnityEngine;

public class Game : MonoBehaviour {
    private Logic logic;
    private BlockView[,] blockViewList;
    private CellView[,] cellViewList;

    public int Width { get; private set; }
    public int Height { get; private set; }

    private void Start()
    {
        Width = 4;
        Height = 4;

        blockViewList = new BlockView[Width, Height];
        for (int i = 0; i < Width; ++i) {
            for (int j = 0; j < Height; ++j) {
                blockViewList[i, j] = (Instantiate(Resources.Load("Prefabs/Block") as GameObject)).GetComponent<BlockView>();
                blockViewList[i, j].transform.position = new Vector2(i, j);
            }
        }

        cellViewList = new CellView[Width, Height];
        for (int i = 0; i < Width; ++i) {
            for (int j = 0; j < Height; ++j) {
                cellViewList[i, j] = (Instantiate(Resources.Load("Prefabs/Cell") as GameObject)).GetComponent<CellView>();
                cellViewList[i, j].transform.position = new Vector2(i, j);
            }
        }

        logic = new Logic();
        logic.Init(Width, Height);

        for (int i = 0; i < Width; ++i) {
            for (int j = 0; j < Height; ++j) {
                logic.Add(i, j);
            }
        }
    }

    public void Move(int x, int y)
    {
        logic.Move(x, y);
    }

    public void RefreshView()
    {
        foreach (var blockView in blockViewList) {
            blockView.enabled = false;
        }

        foreach (var block in logic.BlockList) {
            var blockView = blockViewList[block.X, block.Y];
            blockView.enabled = true;
            blockView.Refresh();
        }
    }
}