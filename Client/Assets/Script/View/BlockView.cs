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
        transform.position = new Vector2(block.X, block.Y);
        text.text = block.Value.ToString();
    }

    public static Vector3 GetScreenPosition(Transform transform, Canvas canvas, Camera cam)
    {
        Vector3 pos;
        float width = canvas.GetComponent<RectTransform>().sizeDelta.x;
        float height = canvas.GetComponent<RectTransform>().sizeDelta.y;
        float x = Camera.main.WorldToScreenPoint(transform.position).x / Screen.width;
        float y = Camera.main.WorldToScreenPoint(transform.position).y / Screen.height;
        pos = new Vector3(width * x - width / 2, y * height - height / 2);
        return pos;
    }
}