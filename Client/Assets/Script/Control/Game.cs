using UnityEngine;

public class Game : MonoBehaviour {
    private Logic logic;
    private BlockView[,] blockViewList;
    private CellView[,] cellViewList;

    public int Width { get; private set; }
    public int Height { get; private set; }

    public GameObject Field;

    private void Start()
    {
        Width = 4;
        Height = 4;

        InitLogic();

        blockViewList = new BlockView[Width, Height];
        for (int i = 0; i < Width; ++i) {
            for (int j = 0; j < Height; ++j) {
                blockViewList[i, j] = (Instantiate(Resources.Load("Prefabs/Block") as GameObject)).GetComponent<BlockView>();
                blockViewList[i, j].Init(logic.Map[i, j]);
                blockViewList[i, j].transform.SetParent(Field.transform);
            }
        }

        cellViewList = new CellView[Width, Height];
        for (int i = 0; i < Width; ++i) {
            for (int j = 0; j < Height; ++j) {
                cellViewList[i, j] = (Instantiate(Resources.Load("Prefabs/Cell") as GameObject)).GetComponent<CellView>();
                cellViewList[i, j].transform.SetParent(Field.transform);
                cellViewList[i, j].transform.localPosition = new Vector2(i, j);
            }
        }

        RefreshView();
    }

    public void InitLogic()
    {
        if(logic == null) {
            logic = new Logic();
        }

        logic.Init(Width, Height);
        Field.gameObject.SetActive(true);
    }

    public bool Move(int x, int y)
    {
        bool changed = logic.Move(x, y);

        if (changed == true) {
            RefreshView();
        }

        return changed;
    }

    public void AddRandom()
    {
        logic.AddRandom();
    }

    public bool IsGameEnd()
    {
        return logic.IsGameEnd();
    }

    public void RefreshView()
    {
        foreach (var blockView in blockViewList) {
            blockView.gameObject.SetActive(false);
        }

        foreach (var block in logic.BlockList) {
            var blockView = blockViewList[block.X, block.Y];
            blockView.gameObject.SetActive(true);

            blockView.SetBlock(block);
            blockView.Refresh();
        }
    }
}