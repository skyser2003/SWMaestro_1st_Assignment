using UnityEngine;

public partial class NetworkClient {
    public void SendHighScorePacket(string name, int score)
    {
        var outPks = new PKS.CS_HIGH_SCORE();
        outPks.name = name;
        outPks.score = score;

        Send(outPks);
    }
}