string in_file_name(string file_input, int idx);
string out_file_name(string file_input, int idx);

void median( string file_input )
{
    string A, B;
    int k_size = 3;

    for (int i = 1; ; i++)
    {
        A = in_file_name(file_input, i);
        //printf("%s", A.c_str());
        Mat srcImage = imread(A);
        Mat dstImage;

        if (srcImage.empty()) break;

        medianBlur(srcImage, dstImage, k_size);
        B = out_file_name(file_input, i);

        imwrite(B, dstImage);

        srcImage.release();
        dstImage.release();

    }
}