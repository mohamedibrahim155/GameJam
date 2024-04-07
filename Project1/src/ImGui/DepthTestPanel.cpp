#include "DepthTestPanel.h"

DepthTestPanel::DepthTestPanel()
{
}

void DepthTestPanel::OnRender(float windowSizeX, float windowSizeY)
{

    if (!isPanelOpen) return;

    ImGuiStyle& style = ImGui::GetStyle();

    float lineHeight = ImGui::GetFontSize() + style.FramePadding.y * 2;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, windowColor);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    if (!ImGui::Begin("Test", &isPanelOpen) || !isEnable)
    {
        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        return;
    }

    ImVec2 viewportSize = ImGui::GetContentRegionAvail();

    isHovered = ImGui::IsWindowHovered();

    float cameraAspectRatio = mResolution.x / mResolution.y;
    float viewportAspectRatio = viewportSize.x / viewportSize.y;

    ImVec2 renderSize;
    ImVec2 renderPos;


    if (viewportAspectRatio > cameraAspectRatio)
    {
        renderSize.y = viewportSize.y;
        renderSize.x = renderSize.y * cameraAspectRatio;
        renderPos.x = (viewportSize.x - renderSize.x) * 0.5f;
        renderPos.y = 0;
    }
    else
    {
        renderSize.x = viewportSize.x;
        renderSize.y = renderSize.x / cameraAspectRatio;
        renderPos.x = 0;
        renderPos.y = (viewportSize.y - renderSize.y) * 0.5f;
    }

    renderPos.y += lineHeight;

    ImVec2 uv0 = ImVec2(0.0f, 1.0f);
    ImVec2 uv1 = ImVec2(1.0f, 0.0f);

    ImGui::SetCursorPos(renderPos);
    ImGui::Image((void*)sceneBuffer->GetColorAttachmentID(), renderSize, uv0, uv1);


    ImGui::End();

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}
