using UnityEngine;

public class BlockView : MonoBehaviour {
    private Block block;

    public void Init(Block block)
    {
        this.block = block;
    }

    public void Refresh()
    {
        transform.position = new Vector2(block.X, block.Y);
    }
}