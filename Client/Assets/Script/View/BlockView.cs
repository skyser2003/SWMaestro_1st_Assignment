using UnityEngine;

public class BlockView : MonoBehaviour {
    private Block block;
    private TextMesh text;

    public void Init(Block block)
    {
        SetBlock(block);
        text = GetComponentInChildren<TextMesh>();
    }

    public void SetBlock(Block block)
    {
        this.block = block;
    }

    public void Refresh()
    {
        transform.localPosition = new Vector3(block.X, block.Y, -1);
        text.text = block.Value.ToString();
    }
}